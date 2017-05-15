import cs50

def main():
    while True:
        print("O hai! How much change is owed?")
        change = cs50.get_float()
        
        if change >= 0:
            break
    
    quarters = 25
    dimes = 10
    nickles = 5
    pennies = 1
    coins = 0
    
    change = int(round(change * 100))
    
    while change >= quarters:
        coins += 1
        change -= 25
        
    while change >= dimes:
        coins += 1
        change -= 10
        
    while change >= nickles:
        coins += 1
        change -= 5
        
    while change >= pennies:
        coins += 1
        change -= 1
        
    print("{}".format(coins))
    
if __name__ == "__main__":
    main()