// Example of the decimal.Negate, decimal.Floor, and decimal.Truncate
// methods.
using System;

class DecimalFloorNegTruncDemo
{
    const string dataFmt = "{0,-30}{1,26}";

    // Display decimal parameters and the method results.
    public static void ShowDecimalFloorNegTrunc( decimal Argument )
    {
        Console.WriteLine( "    // {0}", Argument);
        Console.WriteLine( "    s21_decimal decimal = {0};", getDecimalInit(Argument));
        Console.WriteLine( "    // {0}", decimal.Truncate(Argument));
        Console.WriteLine( "    s21_decimal decimal_check = {0};", getDecimalInit(decimal.Truncate(Argument)));
        Console.WriteLine("");
        Console.WriteLine("    test_truncate(decimal, decimal_check);");
    }
    
    public static string getDecimalInit(decimal value) {
        int[] bits = decimal.GetBits(value);
        string ctor = String.Format(
            "{{{{0x{0:X}", bits[ 0 ] );

        for( int index = 1; index < bits.Length; index++ )
            ctor += String.Format( ", 0x{0:X}", bits[ index ] );
        ctor += "}}";
        return ctor;
    }

    public static void Main( )
    {
        decimal[] numbers = {0M, 1.000M, 123.456M, -123.456M, new decimal( 1230000000, 0, 0, true, 7 ), -9999999999.9999999999M};
        
        int i = 0;
        foreach (decimal number in numbers) {
            i++;
            Console.WriteLine("START_TEST(test_truncate_ok{0}) {{", i);
            ShowDecimalFloorNegTrunc(number);
            Console.WriteLine("}");
            Console.WriteLine("");
        }
    }
}