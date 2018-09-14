/**
 * bcrypto.cc - fast native bindings to crypto functions.
 * Copyright (c) 2016-2017, Christopher Jeffrey (MIT License)
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <node.h>
#include <nan.h>

#include "common.h"
#include "aead.h"
#include "aes.h"
#include "blake2b.h"
#include "chacha20.h"
#include "cipherbase.h"
#if NODE_MAJOR_VERSION >= 10
#include "dsa.h"
#include "ecdsa.h"
#endif
#include "ed25519.h"
#include "hash160.h"
#include "hash256.h"
#include "keccak.h"
#include "md5.h"
#include "poly1305.h"
#include "pbkdf2.h"
#include "random.h"
#include "ripemd160.h"
#if NODE_MAJOR_VERSION >= 10
#include "rsa.h"
#endif
#include "scrypt.h"
#include "sha1.h"
#include "sha224.h"
#include "sha256.h"
#include "sha384.h"
#include "sha512.h"

#include "bcrypto.h"

// For "cleanse"
#include "openssl/crypto.h"

NAN_METHOD(cleanse) {
  if (info.Length() < 1)
    return Nan::ThrowError("cleanse() requires arguments.");

  v8::Local<v8::Object> buf = info[0].As<v8::Object>();

  if (!node::Buffer::HasInstance(buf))
    return Nan::ThrowTypeError("First argument must be a buffer.");

  const uint8_t *data = (const uint8_t *)node::Buffer::Data(buf);
  size_t len = node::Buffer::Length(buf);

  OPENSSL_cleanse((void *)data, len);
}

NAN_MODULE_INIT(init) {
  BAEAD::Init(target);
  BAES::Init(target);
  BBlake2b::Init(target);
  BChaCha20::Init(target);
  BCipherBase::Init(target);
  Nan::Export(target, "cleanse", cleanse);
#if NODE_MAJOR_VERSION >= 10
  BDSA::Init(target);
  BECDSA::Init(target);
#endif
  BED25519::Init(target);
  BHash160::Init(target);
  BHash256::Init(target);
  BKeccak::Init(target);
  BMD5::Init(target);
  BPoly1305::Init(target);
  BPBKDF2::Init(target);
  BRandom::Init(target);
  BRIPEMD160::Init(target);
#if NODE_MAJOR_VERSION >= 10
  BRSA::Init(target);
#endif
  BScrypt::Init(target);
  BSHA1::Init(target);
  BSHA224::Init(target);
  BSHA256::Init(target);
  BSHA384::Init(target);
  BSHA512::Init(target);
}

NODE_MODULE(bcrypto, init)
