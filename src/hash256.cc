#include "common.h"
#include "hash256.h"

SHA256_CTX global_ctx;
static uint8_t global_out[32];

static Nan::Persistent<v8::FunctionTemplate> hash256_constructor;

BHash256::BHash256() {
  memset(&ctx, 0, sizeof(SHA256_CTX));
}

BHash256::~BHash256() {}

void
BHash256::Init(v8::Local<v8::Object> &target) {
  Nan::HandleScope scope;

  v8::Local<v8::FunctionTemplate> tpl =
    Nan::New<v8::FunctionTemplate>(BHash256::New);

  hash256_constructor.Reset(tpl);

  tpl->SetClassName(Nan::New("Hash256").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "init", BHash256::Init);
  Nan::SetPrototypeMethod(tpl, "update", BHash256::Update);
  Nan::SetPrototypeMethod(tpl, "final", BHash256::Final);
  Nan::SetMethod(tpl, "digest", BHash256::Digest);
  Nan::SetMethod(tpl, "root", BHash256::Root);
  Nan::SetMethod(tpl, "multi", BHash256::Multi);

  v8::Local<v8::FunctionTemplate> ctor =
    Nan::New<v8::FunctionTemplate>(hash256_constructor);

  target->Set(Nan::New("Hash256").ToLocalChecked(), ctor->GetFunction());
}

NAN_METHOD(BHash256::New) {
  if (!info.IsConstructCall())
    return Nan::ThrowError("Could not create BHash256 instance.");

  BHash256 *hash = new BHash256();
  hash->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(BHash256::Init) {
  BHash256 *hash = ObjectWrap::Unwrap<BHash256>(info.Holder());

  SHA256_Init(&hash->ctx);

  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(BHash256::Update) {
  BHash256 *hash = ObjectWrap::Unwrap<BHash256>(info.Holder());

  if (info.Length() < 1)
    return Nan::ThrowError("hash256.update() requires arguments.");

  v8::Local<v8::Object> buf = info[0].As<v8::Object>();

  if (!node::Buffer::HasInstance(buf))
    return Nan::ThrowTypeError("First argument must be a buffer.");

  const uint8_t *in = (uint8_t *)node::Buffer::Data(buf);
  size_t inlen = node::Buffer::Length(buf);

  SHA256_Update(&hash->ctx, in, inlen);

  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(BHash256::Final) {
  BHash256 *hash = ObjectWrap::Unwrap<BHash256>(info.Holder());

  SHA256_Final(global_out, &hash->ctx);
  SHA256_Init(&hash->ctx);
  SHA256_Update(&hash->ctx, global_out, 32);
  SHA256_Final(global_out, &hash->ctx);

  info.GetReturnValue().Set(
    Nan::CopyBuffer((char *)&global_out[0], 32).ToLocalChecked());
}

NAN_METHOD(BHash256::Digest) {
  if (info.Length() < 1)
    return Nan::ThrowError("hash256.digest() requires arguments.");

  v8::Local<v8::Object> buf = info[0].As<v8::Object>();

  if (!node::Buffer::HasInstance(buf))
    return Nan::ThrowTypeError("First argument must be a buffer.");

  const uint8_t *in = (uint8_t *)node::Buffer::Data(buf);
  size_t inlen = node::Buffer::Length(buf);

  SHA256_Init(&global_ctx);
  SHA256_Update(&global_ctx, in, inlen);
  SHA256_Final(global_out, &global_ctx);
  SHA256_Init(&global_ctx);
  SHA256_Update(&global_ctx, global_out, 32);
  SHA256_Final(global_out, &global_ctx);

  info.GetReturnValue().Set(
    Nan::CopyBuffer((char *)&global_out[0], 32).ToLocalChecked());
}

NAN_METHOD(BHash256::Root) {
  if (info.Length() < 2)
    return Nan::ThrowError("hash256.root() requires arguments.");

  v8::Local<v8::Object> lbuf = info[0].As<v8::Object>();
  v8::Local<v8::Object> rbuf = info[1].As<v8::Object>();

  if (!node::Buffer::HasInstance(lbuf))
    return Nan::ThrowTypeError("First argument must be a buffer.");

  if (!node::Buffer::HasInstance(rbuf))
    return Nan::ThrowTypeError("Second argument must be a buffer.");

  const uint8_t *left = (uint8_t *)node::Buffer::Data(lbuf);
  const uint8_t *right = (uint8_t *)node::Buffer::Data(rbuf);

  size_t leftlen = node::Buffer::Length(lbuf);
  size_t rightlen = node::Buffer::Length(rbuf);

  if (leftlen != 32 || rightlen != 32)
    return Nan::ThrowTypeError("Bad node sizes.");

  SHA256_Init(&global_ctx);
  SHA256_Update(&global_ctx, left, leftlen);
  SHA256_Update(&global_ctx, right, rightlen);
  SHA256_Final(global_out, &global_ctx);
  SHA256_Init(&global_ctx);
  SHA256_Update(&global_ctx, global_out, 32);
  SHA256_Final(global_out, &global_ctx);

  info.GetReturnValue().Set(
    Nan::CopyBuffer((char *)&global_out[0], 32).ToLocalChecked());
}

NAN_METHOD(BHash256::Multi) {
  if (info.Length() < 2)
    return Nan::ThrowError("hash256.multi() requires arguments.");

  v8::Local<v8::Object> onebuf = info[0].As<v8::Object>();
  v8::Local<v8::Object> twobuf = info[1].As<v8::Object>();

  if (!node::Buffer::HasInstance(onebuf))
    return Nan::ThrowTypeError("First argument must be a buffer.");

  if (!node::Buffer::HasInstance(twobuf))
    return Nan::ThrowTypeError("Second argument must be a buffer.");

  const uint8_t *one = (uint8_t *)node::Buffer::Data(onebuf);
  const uint8_t *two = (uint8_t *)node::Buffer::Data(twobuf);

  size_t onelen = node::Buffer::Length(onebuf);
  size_t twolen = node::Buffer::Length(twobuf);

  uint8_t *three = NULL;
  size_t threelen = 0;

  if (info.Length() > 2 && !IsNull(info[2])) {
    v8::Local<v8::Object> threebuf = info[2].As<v8::Object>();

    if (!node::Buffer::HasInstance(threebuf))
      return Nan::ThrowTypeError("Third argument must be a buffer.");

    three = (uint8_t *)node::Buffer::Data(threebuf);
    threelen = node::Buffer::Length(threebuf);
  }

  SHA256_Init(&global_ctx);
  SHA256_Update(&global_ctx, one, onelen);
  SHA256_Update(&global_ctx, two, twolen);
  if (three)
    SHA256_Update(&global_ctx, three, threelen);
  SHA256_Final(global_out, &global_ctx);
  SHA256_Init(&global_ctx);
  SHA256_Update(&global_ctx, global_out, 32);
  SHA256_Final(global_out, &global_ctx);

  info.GetReturnValue().Set(
    Nan::CopyBuffer((char *)&global_out[0], 32).ToLocalChecked());
}
