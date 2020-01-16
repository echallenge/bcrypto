/* eslint no-nested-ternary: "off" */

'use strict';

const assert = require('bsert');
const bcrypto = require('../');
const {env} = process;
const parts = process.version.split(/[^\d]/);
const NODE_MAJOR = parts[1] >>> 0;
const NODE_MINOR = parts[2] >>> 0;
const HAS_BIGINT = typeof BigInt === 'function' ? 1 : 0;
const FORCE_BIGINT = HAS_BIGINT && env.BCRYPTO_FORCE_BIGINT != null ? 1 : 0;

describe('Bcrypto', function() {
  it('should have correct environment', () => {
    let backend = process.env.NODE_BACKEND;

    if (process.browser && !backend)
      backend = 'js';

    switch (backend) {
      case 'js':
        assert.strictEqual(bcrypto.native, 0);
        assert.strictEqual(bcrypto.AEAD.native, 0);
        assert.strictEqual(bcrypto.aes.native, 0);
        assert.strictEqual(bcrypto.bcrypt.native, 0);
        assert.strictEqual(bcrypto.BLAKE2b.native, 0);
        assert.strictEqual(bcrypto.BLAKE2b160.native, 0);
        assert.strictEqual(bcrypto.BLAKE2b256.native, 0);
        assert.strictEqual(bcrypto.BLAKE2b384.native, 0);
        assert.strictEqual(bcrypto.BLAKE2b512.native, 0);
        assert.strictEqual(bcrypto.BLAKE2s.native, 0);
        assert.strictEqual(bcrypto.BLAKE2s128.native, 0);
        assert.strictEqual(bcrypto.BLAKE2s160.native, 0);
        assert.strictEqual(bcrypto.BLAKE2s224.native, 0);
        assert.strictEqual(bcrypto.BLAKE2s256.native, 0);
        assert.strictEqual(bcrypto.BN.native, FORCE_BIGINT);
        assert.strictEqual(bcrypto.box.native, 0);
        assert.strictEqual(bcrypto.ChaCha20.native, 0);
        assert.strictEqual(bcrypto.cipher.native, 0);
        assert.strictEqual(bcrypto.cleanse.native, 0);
        assert.strictEqual(bcrypto.CSHAKE.native, 0);
        assert.strictEqual(bcrypto.CSHAKE128.native, 0);
        assert.strictEqual(bcrypto.CSHAKE256.native, 0);
        assert.strictEqual(bcrypto.CtrDRBG.native, 0);
        assert.strictEqual(bcrypto.dh.native, 0);
        assert.strictEqual(bcrypto.dsa.native, 0);
        assert.strictEqual(bcrypto.dsaies.native, undefined);
        assert.strictEqual(bcrypto.eb2k.native, 0);
        assert.strictEqual(bcrypto.ecies.native, undefined);
        assert.strictEqual(bcrypto.ed25519.native, 0);
        assert.strictEqual(bcrypto.ed448.native, 0);
        assert.strictEqual(bcrypto.encoding.native, undefined);
        assert.strictEqual(bcrypto.encoding.base58.native, 0);
        assert.strictEqual(bcrypto.encoding.bech32.native, 0);
        assert.strictEqual(bcrypto.encoding.cash32.native, 0);
        assert.strictEqual(bcrypto.GOST94.native, 0);
        assert.strictEqual(bcrypto.Hash160.native, 0);
        assert.strictEqual(bcrypto.Hash256.native, 0);
        assert.strictEqual(bcrypto.HashDRBG.native, 0);
        assert.strictEqual(bcrypto.HKDF.native, 0);
        assert.strictEqual(bcrypto.HmacDRBG.native, 0);
        assert.strictEqual(bcrypto.Keccak.native, 0);
        assert.strictEqual(bcrypto.Keccak224.native, 0);
        assert.strictEqual(bcrypto.Keccak256.native, 0);
        assert.strictEqual(bcrypto.Keccak384.native, 0);
        assert.strictEqual(bcrypto.Keccak512.native, 0);
        assert.strictEqual(bcrypto.KMAC.native, 0);
        assert.strictEqual(bcrypto.KMAC128.native, 0);
        assert.strictEqual(bcrypto.KMAC256.native, 0);
        assert.strictEqual(bcrypto.MD2.native, 0);
        assert.strictEqual(bcrypto.MD4.native, 0);
        assert.strictEqual(bcrypto.MD5.native, 0);
        assert.strictEqual(bcrypto.MD5SHA1.native, 0);
        assert.strictEqual(bcrypto.merkle.native, undefined);
        assert.strictEqual(bcrypto.mrkl.native, undefined);
        assert.strictEqual(bcrypto.murmur3.native, 0);
        assert.strictEqual(bcrypto.p192.native, 0);
        assert.strictEqual(bcrypto.p224.native, 0);
        assert.strictEqual(bcrypto.p256.native, 0);
        assert.strictEqual(bcrypto.p384.native, 0);
        assert.strictEqual(bcrypto.p521.native, 0);
        assert.strictEqual(bcrypto.pbkdf2.native, 0);
        assert.strictEqual(bcrypto.pgp.native, undefined);
        assert.strictEqual(bcrypto.Poly1305.native, 0);
        assert.strictEqual(bcrypto.random.native, 0);
        assert.strictEqual(bcrypto.RC4.native, 0);
        assert.strictEqual(bcrypto.RIPEMD160.native, 0);
        assert.strictEqual(bcrypto.rsa.native, 0);
        assert.strictEqual(bcrypto.rsaies.native, undefined);
        assert.strictEqual(bcrypto.safe.native, undefined);
        assert.strictEqual(bcrypto.Salsa20.native, 0);
        assert.strictEqual(bcrypto.scrypt.native, 0);
        assert.strictEqual(bcrypto.secp256k1.native, 0);
        assert.strictEqual(bcrypto.secretbox.native, 0);
        assert.strictEqual(bcrypto.ssh.native, undefined);
        assert.strictEqual(bcrypto.SHA1.native, 0);
        assert.strictEqual(bcrypto.SHA224.native, 0);
        assert.strictEqual(bcrypto.SHA256.native, 0);
        assert.strictEqual(bcrypto.SHA256.native, 0);
        assert.strictEqual(bcrypto.SHA384.native, 0);
        assert.strictEqual(bcrypto.SHA512.native, 0);
        assert.strictEqual(bcrypto.SHA3.native, 0);
        assert.strictEqual(bcrypto.SHA3_224.native, 0);
        assert.strictEqual(bcrypto.SHA3_256.native, 0);
        assert.strictEqual(bcrypto.SHA3_384.native, 0);
        assert.strictEqual(bcrypto.SHA3_512.native, 0);
        assert.strictEqual(bcrypto.SHAKE.native, 0);
        assert.strictEqual(bcrypto.SHAKE128.native, 0);
        assert.strictEqual(bcrypto.SHAKE256.native, 0);
        assert.strictEqual(bcrypto.siphash.native, 0);
        assert.strictEqual(bcrypto.Whirlpool.native, 0);
        assert.strictEqual(bcrypto.x25519.native, 0);
        assert.strictEqual(bcrypto.x448.native, 0);
        break;
      case 'node':
        assert.strictEqual(bcrypto.native, 1);
        assert.strictEqual(bcrypto.AEAD.native, 0);
        assert.strictEqual(bcrypto.aes.native, 1);
        assert.strictEqual(bcrypto.bcrypt.native, 0);
        if (NODE_MAJOR < 10) {
          assert.strictEqual(bcrypto.BLAKE2b.native, 1);
          assert.strictEqual(bcrypto.BLAKE2b160.native, 1);
          assert.strictEqual(bcrypto.BLAKE2b256.native, 1);
          assert.strictEqual(bcrypto.BLAKE2b384.native, 1);
          assert.strictEqual(bcrypto.BLAKE2b512.native, 1);
          assert.strictEqual(bcrypto.BLAKE2s.native, 1);
          assert.strictEqual(bcrypto.BLAKE2s128.native, 1);
          assert.strictEqual(bcrypto.BLAKE2s160.native, 1);
          assert.strictEqual(bcrypto.BLAKE2s224.native, 1);
          assert.strictEqual(bcrypto.BLAKE2s256.native, 1);
        }
        assert.strictEqual(bcrypto.BN.native, HAS_BIGINT);
        assert.strictEqual(bcrypto.box.native, 0);
        assert.strictEqual(bcrypto.ChaCha20.native, 0);
        assert.strictEqual(bcrypto.cipher.native, 1);
        assert.strictEqual(bcrypto.cleanse.native, 1);
        assert.strictEqual(bcrypto.CSHAKE.native, 0);
        assert.strictEqual(bcrypto.CSHAKE128.native, 0);
        assert.strictEqual(bcrypto.CSHAKE256.native, 0);
        assert.strictEqual(bcrypto.CtrDRBG.native, 0);
        assert.strictEqual(bcrypto.dh.native, 0);
        assert.strictEqual(bcrypto.dsa.native, 1);
        assert.strictEqual(bcrypto.dsaies.native, undefined);
        assert.strictEqual(bcrypto.eb2k.native, 0);
        assert.strictEqual(bcrypto.ecies.native, undefined);
        assert.strictEqual(bcrypto.ed25519.native, NODE_MAJOR >= 12 ? 1 : 0);
        assert.strictEqual(bcrypto.ed448.native, NODE_MAJOR >= 12 ? 1 : 0);
        assert.strictEqual(bcrypto.encoding.native, undefined);
        assert.strictEqual(bcrypto.encoding.base58.native, 0);
        assert.strictEqual(bcrypto.encoding.bech32.native, 0);
        assert.strictEqual(bcrypto.encoding.cash32.native, 0);
        assert.strictEqual(bcrypto.GOST94.native, 0);
        assert.strictEqual(bcrypto.Hash160.native, 1);
        assert.strictEqual(bcrypto.Hash256.native, 1);
        assert.strictEqual(bcrypto.HashDRBG.native, 0);
        assert.strictEqual(bcrypto.HKDF.native, 0);
        assert.strictEqual(bcrypto.HmacDRBG.native, 0);
        assert.strictEqual(bcrypto.Keccak.native, 0);
        assert.strictEqual(bcrypto.Keccak224.native, 0);
        assert.strictEqual(bcrypto.Keccak256.native, 0);
        assert.strictEqual(bcrypto.Keccak384.native, 0);
        assert.strictEqual(bcrypto.Keccak512.native, 0);
        assert.strictEqual(bcrypto.KMAC.native, 0);
        assert.strictEqual(bcrypto.KMAC128.native, 0);
        assert.strictEqual(bcrypto.KMAC256.native, 0);
        assert.strictEqual(bcrypto.MD2.native, 0);
        assert.strictEqual(bcrypto.MD4.native, 1);
        assert.strictEqual(bcrypto.MD5.native, 1);
        assert.strictEqual(bcrypto.MD5SHA1.native, 1);
        assert.strictEqual(bcrypto.merkle.native, undefined);
        assert.strictEqual(bcrypto.mrkl.native, undefined);
        assert.strictEqual(bcrypto.murmur3.native, 0);
        assert.strictEqual(bcrypto.p192.native, 0);
        assert.strictEqual(bcrypto.p224.native, 0);
        assert.strictEqual(bcrypto.p256.native, 0);
        assert.strictEqual(bcrypto.p384.native, 0);
        assert.strictEqual(bcrypto.p521.native, 0);
        assert.strictEqual(bcrypto.pbkdf2.native, 1);
        assert.strictEqual(bcrypto.pgp.native, undefined);
        assert.strictEqual(bcrypto.Poly1305.native, 0);
        assert.strictEqual(bcrypto.random.native, 1);
        assert.strictEqual(bcrypto.RC4.native, 0);
        assert.strictEqual(bcrypto.RIPEMD160.native, 1);
        assert.strictEqual(bcrypto.rsa.native, 1);
        assert.strictEqual(bcrypto.rsaies.native, undefined);
        assert.strictEqual(bcrypto.safe.native, undefined);
        assert.strictEqual(bcrypto.Salsa20.native, 0);
        if (NODE_MAJOR > 10 || (NODE_MAJOR === 10 && NODE_MINOR >= 5))
          assert.strictEqual(bcrypto.scrypt.native, 1);
        else
          assert.strictEqual(bcrypto.scrypt.native, 0);
        assert.strictEqual(bcrypto.secp256k1.native, 0);
        assert.strictEqual(bcrypto.secretbox.native, 0);
        assert.strictEqual(bcrypto.ssh.native, undefined);
        assert.strictEqual(bcrypto.SHA1.native, 1);
        assert.strictEqual(bcrypto.SHA224.native, 1);
        assert.strictEqual(bcrypto.SHA256.native, 1);
        assert.strictEqual(bcrypto.SHA256.native, 1);
        assert.strictEqual(bcrypto.SHA384.native, 1);
        assert.strictEqual(bcrypto.SHA512.native, 1);
        assert.strictEqual(bcrypto.SHA3.native, 1);
        assert.strictEqual(bcrypto.SHA3_224.native, 1);
        assert.strictEqual(bcrypto.SHA3_256.native, 1);
        assert.strictEqual(bcrypto.SHA3_384.native, 1);
        assert.strictEqual(bcrypto.SHA3_512.native, 1);
        assert.strictEqual(bcrypto.SHAKE.native, 0);
        assert.strictEqual(bcrypto.SHAKE128.native, 0);
        assert.strictEqual(bcrypto.SHAKE256.native, 0);
        assert.strictEqual(bcrypto.siphash.native, 0);
        assert.strictEqual(bcrypto.Whirlpool.native, 1);
        assert.strictEqual(bcrypto.x25519.native, 0);
        assert.strictEqual(bcrypto.x448.native, 0);
        break;
      case 'native':
      default:
        assert.strictEqual(bcrypto.native, 2);
        assert.strictEqual(bcrypto.AEAD.native, 2);
        assert.strictEqual(bcrypto.aes.native, 1);
        assert.strictEqual(bcrypto.bcrypt.native, 0);
        assert.strictEqual(bcrypto.BLAKE2b.native, 2);
        assert.strictEqual(bcrypto.BLAKE2b160.native, 2);
        assert.strictEqual(bcrypto.BLAKE2b256.native, 2);
        assert.strictEqual(bcrypto.BLAKE2b384.native, 2);
        assert.strictEqual(bcrypto.BLAKE2b512.native, 2);
        assert.strictEqual(bcrypto.BLAKE2s.native, 2);
        assert.strictEqual(bcrypto.BLAKE2s128.native, 2);
        assert.strictEqual(bcrypto.BLAKE2s160.native, 2);
        assert.strictEqual(bcrypto.BLAKE2s224.native, 2);
        assert.strictEqual(bcrypto.BLAKE2s256.native, 2);
        assert.strictEqual(bcrypto.BN.native, HAS_BIGINT);
        assert.strictEqual(bcrypto.box.native, 0);
        assert.strictEqual(bcrypto.ChaCha20.native, 2);
        assert.strictEqual(bcrypto.cipher.native, 1);
        assert.strictEqual(bcrypto.cleanse.native, 2);
        assert.strictEqual(bcrypto.CSHAKE.native, 2);
        assert.strictEqual(bcrypto.CSHAKE128.native, 2);
        assert.strictEqual(bcrypto.CSHAKE256.native, 2);
        assert.strictEqual(bcrypto.CtrDRBG.native, 0);
        assert.strictEqual(bcrypto.dh.native, 0);
        assert.strictEqual(bcrypto.dsa.native, NODE_MAJOR >= 10 ? 2 : 1);
        assert.strictEqual(bcrypto.dsaies.native, undefined);
        assert.strictEqual(bcrypto.eb2k.native, 0);
        assert.strictEqual(bcrypto.ecies.native, undefined);
        assert.strictEqual(bcrypto.ed25519.native, 2);
        assert.strictEqual(bcrypto.ed448.native, 2);
        assert.strictEqual(bcrypto.encoding.native, undefined);
        assert.strictEqual(bcrypto.encoding.base58.native, 2);
        assert.strictEqual(bcrypto.encoding.bech32.native, 2);
        assert.strictEqual(bcrypto.encoding.cash32.native, 2);
        assert.strictEqual(bcrypto.GOST94.native, 0);
        assert.strictEqual(bcrypto.Hash160.native, 2);
        assert.strictEqual(bcrypto.Hash256.native, 2);
        assert.strictEqual(bcrypto.HashDRBG.native, 0);
        assert.strictEqual(bcrypto.HKDF.native, 0);
        assert.strictEqual(bcrypto.HmacDRBG.native, 0);
        assert.strictEqual(bcrypto.Keccak.native, 2);
        assert.strictEqual(bcrypto.Keccak224.native, 2);
        assert.strictEqual(bcrypto.Keccak256.native, 2);
        assert.strictEqual(bcrypto.Keccak384.native, 2);
        assert.strictEqual(bcrypto.Keccak512.native, 2);
        assert.strictEqual(bcrypto.KMAC.native, 2);
        assert.strictEqual(bcrypto.KMAC128.native, 2);
        assert.strictEqual(bcrypto.KMAC256.native, 2);
        assert.strictEqual(bcrypto.MD2.native, 0);
        assert.strictEqual(bcrypto.MD4.native, 1);
        assert.strictEqual(bcrypto.MD5.native, 2);
        assert.strictEqual(bcrypto.MD5SHA1.native, 2);
        assert.strictEqual(bcrypto.merkle.native, undefined);
        assert.strictEqual(bcrypto.mrkl.native, undefined);
        assert.strictEqual(bcrypto.murmur3.native, 2);
        assert.strictEqual(bcrypto.p192.native, NODE_MAJOR >= 10 ? 2 : 0);
        assert.strictEqual(bcrypto.p224.native, NODE_MAJOR >= 10 ? 2 : 0);
        assert.strictEqual(bcrypto.p256.native, NODE_MAJOR >= 10 ? 2 : 0);
        assert.strictEqual(bcrypto.p384.native, NODE_MAJOR >= 10 ? 2 : 0);
        assert.strictEqual(bcrypto.p521.native, NODE_MAJOR >= 10 ? 2 : 0);
        assert.strictEqual(bcrypto.pbkdf2.native, 2);
        assert.strictEqual(bcrypto.pgp.native, undefined);
        assert.strictEqual(bcrypto.Poly1305.native, 2);
        assert.strictEqual(bcrypto.random.native, 1);
        assert.strictEqual(bcrypto.RC4.native, 0);
        assert.strictEqual(bcrypto.RIPEMD160.native, 2);
        assert.strictEqual(bcrypto.rsa.native, NODE_MAJOR >= 10 ? 2 : 1);
        assert.strictEqual(bcrypto.rsaies.native, undefined);
        assert.strictEqual(bcrypto.safe.native, undefined);
        assert.strictEqual(bcrypto.Salsa20.native, 2);
        assert.strictEqual(bcrypto.scrypt.native, 2);
        assert.strictEqual(bcrypto.secp256k1.native, 2);
        assert.strictEqual(bcrypto.secretbox.native, 0);
        assert.strictEqual(bcrypto.ssh.native, undefined);
        assert.strictEqual(bcrypto.SHA1.native, 2);
        assert.strictEqual(bcrypto.SHA224.native, 2);
        assert.strictEqual(bcrypto.SHA256.native, 2);
        assert.strictEqual(bcrypto.SHA256.native, 2);
        assert.strictEqual(bcrypto.SHA384.native, 2);
        assert.strictEqual(bcrypto.SHA512.native, 2);
        assert.strictEqual(bcrypto.SHA3.native, 2);
        assert.strictEqual(bcrypto.SHA3_224.native, 2);
        assert.strictEqual(bcrypto.SHA3_256.native, 2);
        assert.strictEqual(bcrypto.SHA3_384.native, 2);
        assert.strictEqual(bcrypto.SHA3_512.native, 2);
        assert.strictEqual(bcrypto.SHAKE.native, 2);
        assert.strictEqual(bcrypto.SHAKE128.native, 2);
        assert.strictEqual(bcrypto.SHAKE256.native, 2);
        assert.strictEqual(bcrypto.siphash.native, 2);
        assert.strictEqual(bcrypto.Whirlpool.native, 1);
        assert.strictEqual(bcrypto.x25519.native, 2);
        assert.strictEqual(bcrypto.x448.native, 2);
        break;
    }
  });
});
