#include <assert.h>
#include <string.h>
#include <node.h>
#include <nan.h>

#if NODE_MAJOR_VERSION >= 10

#include "common.h"
#include "ecdsa/ecdsa.h"
#include "ecdsa.h"

void
BECDSA::Init(v8::Local<v8::Object> &target) {
  Nan::HandleScope scope;
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();

  Nan::Export(obj, "privateKeyGenerate", BECDSA::PrivateKeyGenerate);
  Nan::Export(obj, "privateKeyExport", BECDSA::PrivateKeyExport);
  Nan::Export(obj, "privateKeyImport", BECDSA::PrivateKeyImport);
  Nan::Export(obj, "privateKeyTweakAdd", BECDSA::PrivateKeyTweakAdd);
  Nan::Export(obj, "publicKeyCreate", BECDSA::PublicKeyCreate);
  Nan::Export(obj, "publicKeyConvert", BECDSA::PublicKeyConvert);
  Nan::Export(obj, "publicKeyVerify", BECDSA::PublicKeyVerify);
  Nan::Export(obj, "publicKeyTweakAdd", BECDSA::PublicKeyTweakAdd);
  Nan::Export(obj, "sign", BECDSA::Sign);
  Nan::Export(obj, "verify", BECDSA::Verify);
  Nan::Export(obj, "recover", BECDSA::Recover);
  Nan::Export(obj, "ecdh", BECDSA::ECDH);

  target->Set(Nan::New("ecdsa").ToLocalChecked(), obj);
}

NAN_METHOD(BECDSA::PrivateKeyGenerate) {
  if (info.Length() < 1)
    return Nan::ThrowError("ecdsa.privateKeyGenerate() requires arguments.");

  if (!info[0]->IsString())
    return Nan::ThrowTypeError("First argument must be a string.");

  Nan::Utf8String name_(info[0]);
  const char *name = (const char *)*name_;

  uint8_t *priv;
  size_t priv_len;

  if (!bcrypto_ecdsa_privkey_generate(name, &priv, &priv_len))
    return Nan::ThrowError("Could not generate key.");

  return info.GetReturnValue().Set(
    Nan::NewBuffer((char *)priv, priv_len).ToLocalChecked());
}

NAN_METHOD(BECDSA::PrivateKeyExport) {
  if (info.Length() < 2)
    return Nan::ThrowError("ecdsa.privateKeyExport() requires arguments.");

  if (!info[0]->IsString())
    return Nan::ThrowTypeError("First argument must be a string.");

  Nan::Utf8String name_(info[0]);
  const char *name = (const char *)*name_;

  v8::Local<v8::Object> pbuf = info[1].As<v8::Object>();

  if (!node::Buffer::HasInstance(pbuf))
    return Nan::ThrowTypeError("Second argument must be a buffer.");

  bool compress = true;

  if (info.Length() > 2 && !IsNull(info[2])) {
    if (!info[2]->IsBoolean())
      return Nan::ThrowTypeError("Third argument must be a boolean.");

    compress = info[2]->BooleanValue();
  }

  const uint8_t *pd = (uint8_t *)node::Buffer::Data(pbuf);
  size_t pl = node::Buffer::Length(pbuf);

  uint8_t *out;
  size_t out_len;

  if (!bcrypto_ecdsa_privkey_export(name, pd, pl, compress, &out, &out_len))
    return Nan::ThrowError("Could not export key.");

  return info.GetReturnValue().Set(
    Nan::NewBuffer((char *)out, out_len).ToLocalChecked());
}

NAN_METHOD(BECDSA::PrivateKeyImport) {
  if (info.Length() < 2)
    return Nan::ThrowError("ecdsa.privateKeyImport() requires arguments.");

  if (!info[0]->IsString())
    return Nan::ThrowTypeError("First argument must be a string.");

  Nan::Utf8String name_(info[0]);
  const char *name = (const char *)*name_;

  v8::Local<v8::Object> rbuf = info[1].As<v8::Object>();

  if (!node::Buffer::HasInstance(rbuf))
    return Nan::ThrowTypeError("Argument must be a buffer.");

  const uint8_t *rd = (uint8_t *)node::Buffer::Data(rbuf);
  size_t rl = node::Buffer::Length(rbuf);

  uint8_t *out;
  size_t out_len;

  if (!bcrypto_ecdsa_privkey_import(name, rd, rl, &out, &out_len))
    return Nan::ThrowError("Could not import key.");

  return info.GetReturnValue().Set(
    Nan::NewBuffer((char *)out, out_len).ToLocalChecked());
}

NAN_METHOD(BECDSA::PrivateKeyTweakAdd) {
  if (info.Length() < 3)
    return Nan::ThrowError("ecdsa.privateKeyTweakAdd() requires arguments.");

  if (!info[0]->IsString())
    return Nan::ThrowTypeError("First argument must be a string.");

  Nan::Utf8String name_(info[0]);
  const char *name = (const char *)*name_;

  v8::Local<v8::Object> pbuf = info[1].As<v8::Object>();
  v8::Local<v8::Object> tbuf = info[2].As<v8::Object>();

  if (!node::Buffer::HasInstance(pbuf)
      || !node::Buffer::HasInstance(tbuf)) {
    return Nan::ThrowTypeError("Arguments must be buffers.");
  }

  const uint8_t *pd = (uint8_t *)node::Buffer::Data(pbuf);
  size_t pl = node::Buffer::Length(pbuf);

  const uint8_t *td = (uint8_t *)node::Buffer::Data(tbuf);
  size_t tl = node::Buffer::Length(tbuf);

  uint8_t *priv;
  size_t priv_len;

  bool result = bcrypto_ecdsa_privkey_tweak_add(
    name, pd, pl, td, tl, &priv, &priv_len);

  if (!result)
    return Nan::ThrowError("Could not tweak private key.");

  return info.GetReturnValue().Set(
    Nan::NewBuffer((char *)priv, priv_len).ToLocalChecked());
}

NAN_METHOD(BECDSA::PublicKeyCreate) {
  if (info.Length() < 2)
    return Nan::ThrowError("ecdsa.publicKeyCreate() requires arguments.");

  if (!info[0]->IsString())
    return Nan::ThrowTypeError("First argument must be a string.");

  Nan::Utf8String name_(info[0]);
  const char *name = (const char *)*name_;

  v8::Local<v8::Object> pbuf = info[1].As<v8::Object>();

  if (!node::Buffer::HasInstance(pbuf))
    return Nan::ThrowTypeError("Second argument must be a buffer.");

  bool compress = true;

  if (info.Length() > 2 && !IsNull(info[2])) {
    if (!info[2]->IsBoolean())
      return Nan::ThrowTypeError("Third argument must be a boolean.");

    compress = info[2]->BooleanValue();
  }

  const uint8_t *pd = (uint8_t *)node::Buffer::Data(pbuf);
  size_t pl = node::Buffer::Length(pbuf);

  uint8_t *pub;
  size_t pub_len;

  bool result = bcrypto_ecdsa_pubkey_create(
    name, pd, pl, compress, &pub, &pub_len);

  if (!result)
    return Nan::ThrowError("Could not create key.");

  return info.GetReturnValue().Set(
    Nan::NewBuffer((char *)pub, pub_len).ToLocalChecked());
}

NAN_METHOD(BECDSA::PublicKeyConvert) {
  if (info.Length() < 2)
    return Nan::ThrowError("ecdsa.publicKeyConvert() requires arguments.");

  if (!info[0]->IsString())
    return Nan::ThrowTypeError("First argument must be a string.");

  Nan::Utf8String name_(info[0]);
  const char *name = (const char *)*name_;

  v8::Local<v8::Object> pbuf = info[1].As<v8::Object>();

  if (!node::Buffer::HasInstance(pbuf))
    return Nan::ThrowTypeError("Second argument must be a buffer.");

  bool compress = true;

  if (info.Length() > 2 && !IsNull(info[2])) {
    if (!info[2]->IsBoolean())
      return Nan::ThrowTypeError("Third argument must be a boolean.");

    compress = info[2]->BooleanValue();
  }

  const uint8_t *pd = (uint8_t *)node::Buffer::Data(pbuf);
  size_t pl = node::Buffer::Length(pbuf);

  uint8_t *pub;
  size_t pub_len;

  bool result = bcrypto_ecdsa_pubkey_convert(
    name, pd, pl, compress, &pub, &pub_len);

  if (!result)
    return Nan::ThrowError("Could not convert key.");

  return info.GetReturnValue().Set(
    Nan::NewBuffer((char *)pub, pub_len).ToLocalChecked());
}

NAN_METHOD(BECDSA::PublicKeyVerify) {
  if (info.Length() < 2)
    return Nan::ThrowError("ecdsa.publicKeyVerify() requires arguments.");

  if (!info[0]->IsString())
    return Nan::ThrowTypeError("First argument must be a string.");

  Nan::Utf8String name_(info[0]);
  const char *name = (const char *)*name_;

  v8::Local<v8::Object> pbuf = info[1].As<v8::Object>();

  if (!node::Buffer::HasInstance(pbuf))
    return Nan::ThrowTypeError("Second argument must be a buffer.");

  const uint8_t *pd = (uint8_t *)node::Buffer::Data(pbuf);
  size_t pl = node::Buffer::Length(pbuf);

  bool result = bcrypto_ecdsa_pubkey_verify(name, pd, pl);

  return info.GetReturnValue().Set(Nan::New<v8::Boolean>(result));
}

NAN_METHOD(BECDSA::PublicKeyTweakAdd) {
  if (info.Length() < 3)
    return Nan::ThrowError("ecdsa.publicKeyTweakAdd() requires arguments.");

  if (!info[0]->IsString())
    return Nan::ThrowTypeError("First argument must be a string.");

  Nan::Utf8String name_(info[0]);
  const char *name = (const char *)*name_;

  v8::Local<v8::Object> pbuf = info[1].As<v8::Object>();
  v8::Local<v8::Object> tbuf = info[2].As<v8::Object>();

  if (!node::Buffer::HasInstance(pbuf)
      || !node::Buffer::HasInstance(tbuf)) {
    return Nan::ThrowTypeError("Arguments must be buffers.");
  }

  bool compress = true;

  if (info.Length() > 3 && !IsNull(info[3])) {
    if (!info[3]->IsBoolean())
      return Nan::ThrowTypeError("Fourth argument must be a boolean.");

    compress = info[3]->BooleanValue();
  }

  const uint8_t *pd = (uint8_t *)node::Buffer::Data(pbuf);
  size_t pl = node::Buffer::Length(pbuf);

  const uint8_t *td = (uint8_t *)node::Buffer::Data(tbuf);
  size_t tl = node::Buffer::Length(tbuf);

  uint8_t *pub;
  size_t pub_len;

  bool result = bcrypto_ecdsa_pubkey_tweak_add(
    name, pd, pl, td, tl, compress, &pub, &pub_len);

  if (!result)
    return Nan::ThrowError("Could not tweak public key.");

  return info.GetReturnValue().Set(
    Nan::NewBuffer((char *)pub, pub_len).ToLocalChecked());
}

NAN_METHOD(BECDSA::Sign) {
  if (info.Length() < 3)
    return Nan::ThrowError("ecdsa.sign() requires arguments.");

  if (!info[0]->IsString())
    return Nan::ThrowTypeError("First argument must be a string.");

  Nan::Utf8String name_(info[0]);
  const char *name = (const char *)*name_;

  v8::Local<v8::Object> mbuf = info[1].As<v8::Object>();
  v8::Local<v8::Object> pbuf = info[2].As<v8::Object>();

  if (!node::Buffer::HasInstance(mbuf)
      || !node::Buffer::HasInstance(pbuf)) {
    return Nan::ThrowTypeError("Arguments must be buffers.");
  }

  const uint8_t *md = (uint8_t *)node::Buffer::Data(mbuf);
  size_t ml = node::Buffer::Length(mbuf);

  const uint8_t *pd = (uint8_t *)node::Buffer::Data(pbuf);
  size_t pl = node::Buffer::Length(pbuf);

  uint8_t *r;
  size_t rl;
  uint8_t *s;
  size_t sl;

  bool result = bcrypto_ecdsa_sign(name, md, ml, pd, pl, &r, &rl, &s, &sl);

  if (!result)
    return Nan::ThrowError("Could not sign.");

  v8::Local<v8::Array> ret = Nan::New<v8::Array>();
  ret->Set(0, Nan::NewBuffer((char *)r, rl).ToLocalChecked());
  ret->Set(1, Nan::NewBuffer((char *)s, sl).ToLocalChecked());

  info.GetReturnValue().Set(ret);
}

NAN_METHOD(BECDSA::Verify) {
  if (info.Length() < 5)
    return Nan::ThrowError("ecdsa.verify() requires arguments.");

  if (!info[0]->IsString())
    return Nan::ThrowTypeError("First argument must be a string.");

  Nan::Utf8String name_(info[0]);
  const char *name = (const char *)*name_;

  v8::Local<v8::Object> mbuf = info[1].As<v8::Object>();
  v8::Local<v8::Object> rbuf = info[2].As<v8::Object>();
  v8::Local<v8::Object> sbuf = info[3].As<v8::Object>();
  v8::Local<v8::Object> pbuf = info[4].As<v8::Object>();

  if (!node::Buffer::HasInstance(mbuf)
      || !node::Buffer::HasInstance(rbuf)
      || !node::Buffer::HasInstance(sbuf)
      || !node::Buffer::HasInstance(pbuf)) {
    return Nan::ThrowTypeError("Arguments must be buffers.");
  }

  const uint8_t *md = (uint8_t *)node::Buffer::Data(mbuf);
  size_t ml = node::Buffer::Length(mbuf);

  const uint8_t *rd = (uint8_t *)node::Buffer::Data(rbuf);
  size_t rl = node::Buffer::Length(rbuf);

  const uint8_t *sd = (uint8_t *)node::Buffer::Data(sbuf);
  size_t sl = node::Buffer::Length(sbuf);

  const uint8_t *pd = (uint8_t *)node::Buffer::Data(pbuf);
  size_t pl = node::Buffer::Length(pbuf);

  bool result = bcrypto_ecdsa_verify(name, md, ml, rd, rl, sd, sl, pd, pl);

  info.GetReturnValue().Set(Nan::New<v8::Boolean>(result));
}

NAN_METHOD(BECDSA::Recover) {
  if (info.Length() < 5)
    return Nan::ThrowError("ecdsa.recover() requires arguments.");

  if (!info[0]->IsString())
    return Nan::ThrowTypeError("First argument must be a string.");

  Nan::Utf8String name_(info[0]);
  const char *name = (const char *)*name_;

  v8::Local<v8::Object> mbuf = info[1].As<v8::Object>();
  v8::Local<v8::Object> rbuf = info[2].As<v8::Object>();
  v8::Local<v8::Object> sbuf = info[3].As<v8::Object>();

  if (!node::Buffer::HasInstance(mbuf)
      || !node::Buffer::HasInstance(rbuf)
      || !node::Buffer::HasInstance(sbuf)) {
    return Nan::ThrowTypeError("Arguments must be buffers.");
  }

  if (!info[4]->IsNumber())
    return Nan::ThrowTypeError("Argument must be a number.");

  int param = (int)info[4]->Uint32Value();
  bool compress = true;

  if (info.Length() > 5 && !IsNull(info[5])) {
    if (!info[5]->IsBoolean())
      return Nan::ThrowTypeError("Argument must be a boolean.");

    compress = info[5]->BooleanValue();
  }

  const uint8_t *md = (uint8_t *)node::Buffer::Data(mbuf);
  size_t ml = node::Buffer::Length(mbuf);

  const uint8_t *rd = (uint8_t *)node::Buffer::Data(rbuf);
  size_t rl = node::Buffer::Length(rbuf);

  const uint8_t *sd = (uint8_t *)node::Buffer::Data(sbuf);
  size_t sl = node::Buffer::Length(sbuf);

  uint8_t *pub;
  size_t pub_len;

  bool result = bcrypto_ecdsa_recover(
    name, md, ml, rd, rl, sd, sl, param, compress, &pub, &pub_len);

  if (!result)
    return info.GetReturnValue().Set(Nan::Null());

  return info.GetReturnValue().Set(
    Nan::NewBuffer((char *)pub, pub_len).ToLocalChecked());
}

NAN_METHOD(BECDSA::ECDH) {
  if (info.Length() < 3)
    return Nan::ThrowError("ecdsa.publicKeyConvert() requires arguments.");

  if (!info[0]->IsString())
    return Nan::ThrowTypeError("First argument must be a string.");

  Nan::Utf8String name_(info[0]);
  const char *name = (const char *)*name_;

  v8::Local<v8::Object> kbuf = info[1].As<v8::Object>();
  v8::Local<v8::Object> pbuf = info[2].As<v8::Object>();

  if (!node::Buffer::HasInstance(kbuf)
      || !node::Buffer::HasInstance(pbuf)) {
    return Nan::ThrowTypeError("Arguments must be buffers.");
  }

  bool compress = true;

  if (info.Length() > 3 && !IsNull(info[3])) {
    if (!info[3]->IsBoolean())
      return Nan::ThrowTypeError("Fourth argument must be a boolean.");

    compress = info[3]->BooleanValue();
  }

  const uint8_t *kd = (uint8_t *)node::Buffer::Data(kbuf);
  size_t kl = node::Buffer::Length(kbuf);

  const uint8_t *pd = (uint8_t *)node::Buffer::Data(pbuf);
  size_t pl = node::Buffer::Length(pbuf);

  uint8_t *secret;
  size_t secret_len;

  bool result = bcrypto_ecdsa_ecdh(
    name, kd, kl, pd, pl, compress, &secret, &secret_len);

  if (!result)
    return Nan::ThrowError("Could not perform ECDH.");

  return info.GetReturnValue().Set(
    Nan::NewBuffer((char *)secret, secret_len).ToLocalChecked());
}

#endif
