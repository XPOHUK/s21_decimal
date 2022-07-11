using System;
class fromIntToDecimalTests {
    static void Main() {
        int[] numbers = {Int32.MinValue, Int32.MinValue + 1, Int32.MinValue / 10, Int32.MinValue / 10000,
        -1000, -1, 0, 1, 1000,
        Int32.MaxValue / 10000, Int32.MaxValue / 10, Int32.MaxValue - 1, Int32.MaxValue};
        decimal result;
        int i = 0;
        foreach (int number in numbers) {
            i++;
            result = Convert.ToDecimal(number);
            Console.WriteLine("START_TEST(test_from_int_to_decimal_ok{0}) {{", i);
            Console.WriteLine("    int number = {0};", number);
            Console.WriteLine("    // Converted the Int32 value {0} to the Decimal value {1}.",
                            number, result);
            Console.WriteLine("    s21_decimal decimal_check = {0};", getDecimalInit(result));
            Console.WriteLine("");
            Console.WriteLine("    test_from_int_to_decimal(number, decimal_check);");
            Console.WriteLine("}");
            Console.WriteLine("");
        }
        
        i = 0;
        foreach (int number in numbers) {
            i++;
            Console.WriteLine("tcase_add_test(tc_core, test_from_int_to_decimal_ok{0});", i);
        }
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
}
