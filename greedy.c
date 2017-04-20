#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float change;
    int quarters = 25;
    int dimes = 10;
    int nickels = 5;
    int pennies = 1;
    int coins = 0;
    
    do
    {
        printf("O hai! How much change is owed?\n");
        change = get_float();
    }
    while (change <= 0);
    
    change = (int)round(change * 100);
    
    while (change >= quarters)
    {
        coins++;
        change = change - 25;
    }
    
    while (change >= dimes)
    {
        coins++;
        change = change - 10;
    }
    
    while (change >= nickels)
    {
        coins++;
        change = change - 5;
    }
    
    while (change >= pennies)
    {
        coins++;
        change = change - 1;
    }
    
    printf("%i\n", coins);
}