from cryptography.hazmat.primitives.asymmetric import rsa, padding
from cryptography.hazmat.primitives import hashes

def generate_rsa_keypair():
    return rsa.generate_private_key(public_exponent=65537, key_size=2048)

def encrypt(public_key, plaintext):
    return public_key.encrypt(plaintext, padding.OAEP(mgf=padding.MGF1(algorithm=hashes.SHA256()), algorithm=hashes.SHA256(), label=None))

def decrypt(private_key, ciphertext):
    return private_key.decrypt(ciphertext, padding.OAEP(mgf=padding.MGF1(algorithm=hashes.SHA256()), algorithm=hashes.SHA256(), label=None))

def main():
    # Bob's initial key pair
    private_key = generate_rsa_keypair()
    public_key = private_key.public_key()

    # Encrypt and decrypt a message
    plaintext = b"Hello, RSA!"
    print(f"Decrypted: {decrypt(private_key, encrypt(public_key, plaintext)).decode()}")

    # Generate new key pair (not keeping the same modulus)
    new_private_key = generate_rsa_keypair()
    new_public_key = new_private_key.public_key()

    try:
        decrypt(private_key, encrypt(new_public_key, plaintext))
        print("Decrypted with old private key!")
    except:
        print("Failed to decrypt with old private key.")

if _name_ == "_main_":
    main()
