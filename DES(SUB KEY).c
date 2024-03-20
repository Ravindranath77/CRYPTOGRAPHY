def left_shift(bits, n):
    return (bits << n) & 0xFFFFFFF | (bits >> (28 - n))

def generate_subkeys(initial_key):
    subkeys = []
    left_part = (initial_key >> 28) & 0xFFFFFFF
    right_part = initial_key & 0xFFFFFFF
    
    for i in range(16):
        left_part = left_shift(left_part, 1)
        right_part = left_shift(right_part, 1)
        
        subkey = (left_part << 28) | right_part
        subkeys.append(subkey)
    
    return subkeys

def main():
    initial_key = 0x123456789ABC  # 48-bit initial key
    subkeys = generate_subkeys(initial_key)
    
    for i, subkey in enumerate(subkeys):
        print(f"Subkey {i+1}: {subkey:012X}")

if __name__ == "__main__":
    main()
