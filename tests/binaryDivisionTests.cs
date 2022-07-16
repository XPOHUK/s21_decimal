// Example of the decimal.Negate, decimal.Floor, and decimal.Truncate
// methods.
using System;

class BinaryDivisionTests
{
    public static void printDivTest(decimal dividend, decimal divisor)
    {
        Console.WriteLine( "    // Delimoe");
        if (dividend == 0 && getSign(dividend) != 0) {
            Console.WriteLine( "    // -{0}", dividend);
        } else {
            Console.WriteLine( "    // {0}", dividend);
        }
        Console.WriteLine( "    s21_decimal dividend = {0};", getDecimalInit(dividend));
        
        Console.WriteLine( "    // Delitel");
        if (divisor == 0 && getSign(divisor) != 0) {
            Console.WriteLine( "    // -{0}", divisor);
        } else {
            Console.WriteLine( "    // {0}", divisor);
        }
        Console.WriteLine( "    s21_decimal divisor = {0};", getDecimalInit(divisor));

        decimal quotient = decimal.Truncate(dividend / divisor);
        decimal remainder = Decimal.Remainder(dividend, divisor);

        try {
            decimal restore = quotient * divisor + remainder;
            if (restore != dividend) {
                quotient = quotient - 1;
                Console.WriteLine( "    // restore != dividend");
            }
        } catch (Exception ex) {
            quotient = quotient - 1;
            Console.WriteLine( "    // OverflowException");
        }

        Console.WriteLine( "    // Chastnoe");
        if (quotient == 0 && getSign(quotient) != 0) {
            Console.WriteLine( "    // -{0}", quotient);
        } else {
            Console.WriteLine( "    // {0}", quotient);
        }
        Console.WriteLine( "    s21_decimal quotient = {0};", getDecimalInit(quotient));

        Console.WriteLine( "    // Ostatok");
        if (remainder == 0 && getSign(remainder) != 0) {
            Console.WriteLine( "    // -{0}", remainder);
        } else {
            Console.WriteLine( "    // {0}", remainder);
        }
        Console.WriteLine( "    s21_decimal remainder = {0};", getDecimalInit(remainder));
        
        Console.WriteLine("");
        Console.WriteLine("    test_binary_division(dividend, divisor, quotient, remainder);");
    }

    public static string getDecimalInit(decimal value) {
        int[] bits = decimal.GetBits(value);
        string ctor = String.Format(
            "{{{{0x{0:X}", bits[ 0 ]);

        for( int index = 1; index < bits.Length; index++ )
            ctor += String.Format( ", 0x{0:X}", bits[ index ] );
        ctor += "}}";
        return ctor;
    }
    
    public static int getSign(decimal value) {
        int[] bits = decimal.GetBits(value);
        return (bits[3] & (1 << 31));
    }
    
    public static int nextInt32() {
        var rng = new Random();
         int firstBits = rng.Next(0, 1 << 4) << 28;
         int lastBits = rng.Next(0, 1 << 28);
         return firstBits | lastBits;
    }
    
    public static decimal randomDecimal() {
        var rng = new Random();
        return new decimal(nextInt32(), nextInt32(), nextInt32(), true, 0);
    }

    public static void Main( )
    {   
        decimal[] dividends = {
            Decimal.MaxValue,
            Decimal.MaxValue - 1,
            52818775009509558395695966890M,
            52818775009509558392832655360M,
            52818774997211729016086244010M,
            52818774997211729013222932480M,
            12297829382473034410M,
            12297829379609722880M,
            2863311530M,
            26409387504754779197847983445M,
            26409387504754779196416327680M,
            26409387498605864508043122005M,
            26409387498605864506611466240M,
            6148914691236517205M,
            6148914689804861440M,
            1431655765M,
            18446744078004518913M,
            18446744078004518912M,
            18446744073709551617M,
            18446744073709551616M,
            4294967297M,
            4294967296M,
            1M,
            39614081266355540835774234624M,
            39614081266355540833626750976M,
            39614081257132168798919458816M,
            39614081257132168796771975168M,
            9223372039002259456M,
            9223372036854775808M,
            2147483648M,
            156064767562212695305426944M,
            156064767562212695296966656M,
            156064767525876035030685696M,
            156064767525876035022225408M,
            36336660283201536M,
            36336660274741248M,
            8460288M,
            79228162514264337593543950335M,
            79228162514264337589248983040M,
            79228162495817593524129366015M,
            79228162495817593519834398720M,
            18446744073709551615M,
            18446744069414584320M,
            4294967295M,
            new decimal (0, 0, 0, false, 0),
            551M,
            5M
        };
        
        decimal[] divisors = {
            Decimal.MaxValue,
            Decimal.MaxValue - 1,
            52818775009509558395695966890M,
            52818775009509558392832655360M,
            52818774997211729016086244010M,
            52818774997211729013222932480M,
            12297829382473034410M,
            12297829379609722880M,
            2863311530M,
            26409387504754779197847983445M,
            26409387504754779196416327680M,
            26409387498605864508043122005M,
            26409387498605864506611466240M,
            6148914691236517205M,
            6148914689804861440M,
            1431655765M,
            18446744078004518913M,
            18446744078004518912M,
            18446744073709551617M,
            18446744073709551616M,
            4294967297M,
            4294967296M,
            1M,
            39614081266355540835774234624M,
            39614081266355540833626750976M,
            39614081257132168798919458816M,
            39614081257132168796771975168M,
            9223372039002259456M,
            9223372036854775808M,
            2147483648M,
            156064767562212695305426944M,
            156064767562212695296966656M,
            156064767525876035030685696M,
            156064767525876035022225408M,
            36336660283201536M,
            36336660274741248M,
            8460288M,
            79228162514264337593543950335M,
            79228162514264337589248983040M,
            79228162495817593524129366015M,
            79228162495817593519834398720M,
            18446744073709551615M,
            18446744069414584320M,
            4294967295M,
            2M,
            5M,
            10M
        };
        
        Console.WriteLine("");
        Console.WriteLine("/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
        Console.WriteLine("Tests for correct data (automatic)");
        Console.WriteLine("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */");
        Console.WriteLine("");

        int i = 0;
        foreach (decimal dividend in dividends) {
            foreach (decimal divisor in divisors) {
                i++;
                Console.WriteLine("START_TEST(test_binary_division_ok{0}) {{", i);
                printDivTest(dividend, divisor);
                Console.WriteLine("}");
                Console.WriteLine("");
            }
        }
        
        i = 0;
        int suit_num = 1;
        foreach (decimal dividend in dividends) {
            foreach (decimal divisor in divisors) {
            if (i % 400 == 0) {
                Console.WriteLine("Suite * binary_division_suite{0}(void) {{", suit_num);
                Console.WriteLine("    Suite *s;");
                Console.WriteLine("    TCase *tc_core;");
                Console.WriteLine("");
                Console.WriteLine("    s = suite_create(\"binary_division{0}\");", suit_num);
                Console.WriteLine("    tc_core = tcase_create(\"Core\");");
                suit_num++;
            }
            i++;
            Console.WriteLine("    tcase_add_test(tc_core, test_binary_division_ok{0});", i);
            if (i % 400 == 0) {
                Console.WriteLine("");
                Console.WriteLine("    suite_add_tcase(s, tc_core);");
                Console.WriteLine("    return s;");
                Console.WriteLine("}");
                Console.WriteLine("");
            }
            }
        }
        if (i % 400 != 0) {
            Console.WriteLine("");
            Console.WriteLine("    suite_add_tcase(s, tc_core);");
            Console.WriteLine("    return s;");
            Console.WriteLine("}");
            Console.WriteLine("");
        }
    }
}