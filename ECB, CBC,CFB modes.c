from cryptography.hazmat.primitives import padding
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend

def add_padding(data, block_size):
    padder = padding.PKCS7(block_size * 8).padder()
    return padder.update(data) + padder.finalize()

def remove_padding(padded_data):
    unpadder = padding.PKCS7(128).unpadder()
    return unpadder.update(padded_data) + unpadder.finalize()

def encrypt_decrypt(mode, key, iv, data):
    cipher = Cipher(algorithms.AES(key), mode, backend=default_backend())
    encryptor = cipher.encryptor()
    ciphertext = encryptor.update(add_padding(data, 16)) + encryptor.finalize()
    decryptor = cipher.decryptor()
    decrypted = remove_padding(decryptor.update(ciphertext) + decryptor.finalize())
    return ciphertext, decrypted

def main():
    key = b"this_is_a_16_key"
    iv = b"this_is_a_16_iv_"  # IV size should match block size (16 bytes)
    data = b"This is a plaintext message for testing."

    print("Original Data:", data)

    ecb_cipher, ecb_decrypted = encrypt_decrypt(modes.ECB(), key, iv, data)
    print("ECB Ciphertext:", ecb_cipher)
    print("ECB Decrypted:", ecb_decrypted)

    cbc_cipher, cbc_decrypted = encrypt_decrypt(modes.CBC(iv), key, iv, data)
    print("CBC Ciphertext:", cbc_cipher)
    print("CBC Decrypted:", cbc_decrypted)

    cfb_cipher, cfb_decrypted = encrypt_decrypt(modes.CFB(iv), key, iv, data)
    print("CFB Ciphertext:", cfb_cipher)
    print("CFB Decrypted:", cfb_decrypted)

if _name_ == "_main_":
    main()
