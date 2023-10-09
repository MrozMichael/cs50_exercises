//credit card validator exercise from cs50
#include <cs50.h>
#include <stdio.h>

long get_card(void);
bool validate(long card, int length);
int get_length(long card);
string get_type(long card, int length);
long cut_off(int digits);

int main(void)
{
    long card = get_card();
    int length = get_length(card);
    string type = get_type(card, length);
    bool valid = validate(card, length);
    if (!valid){
        type = "INVALID\n";
    }
    printf("%s", type);
}

long get_card(void)
{

    long card_num= get_long("Number: ");
    int length = get_length(card_num);
    if (length < 13 || length > 16){
        return 0; //will trigger INVALID in get_type
    }
    return card_num;
}

int get_length(long card)
{
    int length = 0;
    long n = card;
    while (n > 0)
    {
        n = n / 10;
        length++;
    }
    return length;
}

string get_type(long card, int length)
{

    long amex_divisor = cut_off(13);       // check first two digits of 15 digit num
    long mastercard_divisor = cut_off(14); // check first two digits of 16 digit num
    long small_visa_divisor = cut_off(12); // check first digit of 13 digit num
    long large_visa_divisor = cut_off(15); // check first of 16 digit num

    // check if amex card
    if (length == 15)
    {
        int first_two = card / amex_divisor;
        if (first_two == 34 || first_two == 37)
        {
            return "AMEX\n";
        }
    }
    // check if mastercard or large visa
    else if (length == 16)
    {
        int first = card / large_visa_divisor;
        if (first == 4){
            return "VISA\n";
        }
        int first_two = card / mastercard_divisor;
        if (first_two >= 51 && first_two <= 55)
        {
            return "MASTERCARD\n";
        }
    }
    // check if small visa
    else if (length == 13)
    {
        int first = card / small_visa_divisor;
        if (first == 4)
        {
            return "VISA\n";
        }
    }
    return "INVALID\n";
}

bool validate(long card, int length)
{
    // apply luhns
    bool skip = true; //invert every iteration;
    long card_num = card; //value to reduce during loop
    int sum = 0;
    for(int i = 0; i < length; i++){
        int digit = card_num % 10; //get least significant num
        if (skip){
            skip = !skip; //set flag to false to get next digit
            card_num /= 10;
            sum+= digit;
            continue;
        }
        skip = !skip; //set flag to true to skip next digit
        card_num /= 10;
        int product = digit * 2;
        while(product > 0){
            digit = product % 10;
            sum += digit;
            product /= 10;
        }
    }
   if(sum % 10 == 0){
    return true;
   }
   return false;
}

long cut_off(int digits)
{ // if digits = 2, return 100 so that num can be divided by 100 to 'cut off' last 2 digits.
    long divisor = 10;
    for (int i = 1; i < digits; i++)
    {
        divisor *= 10;
    }
    return divisor;
}