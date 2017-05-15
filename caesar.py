import cs50
import sys

def main():
    # Validate command line input from user
    if len(sys.argv) != 2:
        print("Missing command-line argument or more than one command line argument entered")
        
        # Print return value for error
        exit(1)
    
    # Convert key to integer    
    key = int(sys.argv[1])
    
    # Get plaintext from user
    print("plaintext: ", end = "")
    plaintext = cs50.get_string()
    
    # Print ciphertext
    print("ciphertext: ", end = "")
    ciphertext(plaintext, key)
    
    # Print return value
    exit(0)

# Function to convert plaintext to ciphetext    
def ciphertext(plaintext, key):
    
    # Iterate over each character in plaintext
    for ch in plaintext:
        
        # Check if character is in uppercase
        if ch.isupper():
            
            # Convert the character accordingly and store it's ASCII value in a
            a = ((ord(ch) - 65 + key) % 26) + 65
            
            # Print by converting int value of a to char
            print("{}".format(chr(a)), end = "")
                
        # Check if character is in lowercase        
        elif ch.islower():
            
            # Convert the character accordingly and store it's ASCII value in b
            b = ((ord(ch) - 97 + key) % 26) + 97
            
            # Print by converting int value of b to char
            print("{}".format(chr(b)), end = "")
        
        # Check if any other value        
        else:
            # Print without any conversion
            print("{}".format(ch), end = "")
    
    # Print new line after printing cihertext            
    print("")
        
if __name__ == "__main__":
    main()