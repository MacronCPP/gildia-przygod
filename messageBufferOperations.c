
unsigned char messageBuffer[64];

void copyToBuffer(unsigned char bank, unsigned char value[])
{
    unsigned char savedBank = currentBank, iterator = 0;
    if(bank != 0) {
        SWITCH_ROMS(bank);
    }
    do
    {
        messageBuffer[iterator] = value[iterator];
        iterator++;
    } while(value[iterator-1] != '|' && value + iterator < messageBuffer + 64);
    if(bank != 0) {
        SWITCH_ROMS(savedBank);
    }
}

void replaceInBuffer(unsigned char bank, unsigned char value[])
{
    unsigned char* current = messageBuffer, *temp;
    unsigned char valueLength = 0, savedBank = currentBank;
    if(bank != 0)
    {
        SWITCH_ROMS(bank);
    }
    while(*current != '%')current++;
    while(value[valueLength] != '|' && value[valueLength] && valueLength < 64)valueLength++;
    temp = current;
    valueLength--;
    while(*temp != '|')temp++;
    while(temp >= current)
    {
        *(temp+valueLength) = *temp;
        temp--;
    }
    temp++;
    while(temp < (current+valueLength+1))
    {
        *temp = *value;
        temp++;
        value++;
    }
    if(bank != 0)
    {
        SWITCH_ROMS(savedBank);
    }
}


void replaceInBufferInt(int value)
{
    int valueCopy = value;
    unsigned char* current = messageBuffer, *temp;
    unsigned char valueLength = 0;
    while(*current != '%')current++;
    do
    {
        valueCopy /= 10;
        valueLength++;
    } while(valueCopy);
    valueCopy = value;
    temp = current;
    if(value >= 0)valueLength--;
    else value = ~value+1;
    while(*temp != '|')temp++;
    while(temp >= current)
    {
        *(temp+valueLength) = *temp;
        temp--;
    }
    temp = (current+valueLength);
    do
    {
        *temp = (value%10) + '0';
        temp--;
        value /= 10;
    } while(value);
    if(valueCopy < 0)
        *temp = '-';
}
