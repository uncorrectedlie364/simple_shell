#include <stdio.h>

/*
 * celsius_to_fahrenheit _ function to convert Celsius to Fahrenheit
 * @celsius: temperature in Celsius as afloat
 *
 * Return: temperarure in Fahrenheit as a float
 */
float celsius_to_fahrenheit(float celsius)
{
	return ((celsius * 9.0 / 5.0) + 32.0);
}

/*
 * main - entry point of the program
 *
 * Return: always 0(success)
 */
int main(void)
{
	float celsius, fahrenheit;

	printf("Enter a temperature in Celsius: ");
	scanf("%f", &celsius);

	fahrenheit = celsius_to_fahrenheit(celsius);

	printf("%.2f Celsius is equal to %.2f Fahrenheit.\n", celsius, fahrenheit);

	return (0);
}
