using System;

class FromDecimalToFloat
{
    public static void ShowTestOk(decimal Argument) {
        if (Argument == 0 && getSign(Argument) != 0) {
            Console.WriteLine( "    // -{0}", Argument);
        } else {
            Console.WriteLine( "    // {0}", Argument);
        }
        Console.WriteLine( "    s21_decimal decimal = {0};", getDecimalInit(Argument));

        Console.WriteLine( "    int check = {0};", BitConverter.SingleToInt32Bits(decimal.ToSingle(Argument)));
        Console.WriteLine("");
        Console.WriteLine("    test_from_decimal_to_float(decimal, check);");
    }
    
    public static void ShowTestFail(decimal Argument) {
        if (Argument == 0 && getSign(Argument) != 0) {
            Console.WriteLine( "    // -{0}", Argument);
        } else {
            Console.WriteLine( "    // {0}", Argument);
        }
        Console.WriteLine( "    s21_decimal decimal = {0};", getDecimalInit(Argument));
        Console.WriteLine("");
        Console.WriteLine("    test_from_decimal_to_float_fail(decimal);");
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
        int b0 = 0;
        int b1 = 0;
        int b2 = 0;
        byte scale = 0;
        bool sign = false;
        
        var rng = new Random();
        b0 = nextInt32();
        sign = rng.Next(2) == 1;
        scale = (byte) rng.Next(29);
        b1 = nextInt32();
        b2 = nextInt32();

        return new decimal(b0, b1, b2, sign, scale);
    }

    public static void Main( )
    {   
        Console.OutputEncoding = System.Text.Encoding.UTF8;
        decimal[] decimal_max = new decimal[29 + 29];
        
        for (int k = 0; k < 29; k++) {
            if (k == 0) {
                decimal_max[k] = Decimal.MaxValue;
            } else {
                decimal_max[k] = decimal_max[k - 1] / 10;
            }
        }

        for (int k = 29; k < 29+29; k++) {
            if (k == 29) {
                decimal_max[k] = Decimal.MaxValue - 1;
            } else {
                decimal_max[k] = decimal_max[k - 1] / 10;
            }
        }

        decimal[] decimal_random = new decimal[100];
        
        for (int k = 0; k < 100; k++) {
            decimal_random[k] = randomDecimal();
        }

        decimal[] numbers = {
            52818775009509558395695966890M, 5281877500950955839569596689.0M, 528187750.09509558395695966890M, 5.2818775009509558395695966890M, // 10101010 10101010 10101010
            52818775009509558392832655360M, 5281877500950955839283265536.0M, 528187750.09509558392832655360M, 5.2818775009509558392832655360M, // 10101010 10101010 00000000
            52818774997211729016086244010M, 5281877499721172901608624401.0M, 528187749.97211729016086244010M, 5.2818774997211729016086244010M, // 10101010 00000000 10101010
            52818774997211729013222932480M, 5281877499721172901322293248.0M, 528187749.97211729013222932480M, 5.2818774997211729013222932480M, // 10101010 00000000 00000000
            12297829382473034410M, 1229782938247303441.0M, 122978293.82473034410M, 1.2297829382473034410M, // 00000000 10101010 10101010
            12297829379609722880M, 1229782937960972288.0M, 122978293.79609722880M, 1.2297829379609722880M, // 00000000 10101010 00000000
            2863311530M, 286331153.0M, 286331.1530M, 2.863311530M, // 00000000 00000000 10101010
            26409387504754779197847983445M, 2640938750475477919784798344.5M, 264093875.04754779197847983445M, 2.6409387504754779197847983445M, // 01010101 01010101 01010101
            26409387504754779196416327680M, 2640938750475477919641632768.0M, 264093875.04754779196416327680M, 2.6409387504754779196416327680M, // 01010101 01010101 00000000
            26409387498605864508043122005M, 2640938749860586450804312200.5M, 264093874.98605864508043122005M, 2.6409387498605864508043122005M, // 01010101 00000000 01010101
            26409387498605864506611466240M, 2640938749860586450661146624.0M, 264093874.98605864506611466240M, 2.6409387498605864506611466240M, // 01010101 00000000 00000000
            6148914691236517205M, 614891469123651720.5M, 6148914.691236517205M, 6.148914691236517205M, // 00000000 01010101 01010101
            6148914689804861440M, 614891468980486144.0M, 6148914.689804861440M, 6.148914689804861440M, // 00000000 01010101 00000000
            1431655765M, 143165576.5M, 143165.5765M, 1.431655765M, // 00000000 00000000 01010101
            18446744078004518913M, 1844674407800451891.3M, 184467440.78004518913M, 1.8446744078004518913M, // 00000001 00000001 00000001
            18446744078004518912M, 1844674407800451891.2M, 18446744.078004518912M, 1.8446744078004518912M, 
            18446744073709551617M, 1844674407370955161.7M, 1844674.4073709551617M, 1.8446744073709551617M, 
            18446744073709551616M, 1844674407370955161.6M, 184467.44073709551616M, 1.8446744073709551616M, 
            4294967297M, 429496729.7M, 42949672.97M, 429496.7297M, 4.294967297M, 42.94967297M, 
            4294967296M, 429496729.6M, 42949672.96M, 4294967.296M, 4.294967296M,  42.94967296M, 
            new decimal (1, 0, 0, false, 1), new decimal (1, 0, 0, false, 13), new decimal (1, 0, 0, false, 14), new decimal (1, 0, 0, false, 27), new decimal (1, 0, 0, false, 28),
            39614081266355540835774234624M, 3961408126635554083577423462.4M, 396140812.66355540835774234624M, 3.9614081266355540835774234624M, // 10000000 00000000 00000000 00000000
            39614081266355540833626750976M, 3961408126635554083362675097.6M, 39614081.266355540833626750976M, 3.9614081266355540833626750976M, 
            39614081257132168798919458816M, 3961408125713216879891945881.6M, 3961408.1257132168798919458816M, 3.9614081257132168798919458816M, 
            39614081257132168796771975168M, 3961408125713216879677197516.8M, 396140.81257132168796771975168M, 3.9614081257132168796771975168M, 
            9223372039002259456M, 922337203900225945.6M, 922337203.9002259456M, 9.223372039002259456M, 
            9223372036854775808M, 922337203685477580.8M, 92233720.36854775808M, 9.223372036854775808M, 
            2147483648M, 214748364.8M, 21474836.48M, 214748.3648M, 21.47483648M, 2.147483648M, 
            156064767562212695305426944M, 15606476756221269530542694.4M, 1560647.67562212695305426944M, 1.56064767562212695305426944M, // 00000000 10000001 00011000 00000000 00000000 10000001 00011000 00000000 00000000 10000001 00011000 00000000
            156064767562212695296966656M, 15606476756221269529696665.6M, 15606476.7562212695296966656M, 1.56064767562212695296966656M, 
            156064767525876035030685696M, 15606476752587603503068569.6M, 156064.767525876035030685696M, 1.56064767525876035030685696M, 
            156064767525876035022225408M, 15606476752587603502222540.8M, 15606.4767525876035022225408M, 1.56064767525876035022225408M, 
            36336660283201536M, 3633666028320153.6M, 363366602.83201536M, 3.6336660283201536M, 
            36336660274741248M, 3633666027474124.8M, 3633666.0274741248M, 363366602.74741248M, 36.336660274741248M, 3.6336660274741248M, 
            8460288M, 846028.8M, 84602.88M, 8460.288M, 84.60288M, 8.460288M, 
            79228162514264337593543950335M, 7922816251426433759354395033.5M, 792281625.14264337593543950335M, 7.9228162514264337593543950335M, // 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111
            79228162514264337589248983040M, 7922816251426433758924898304.0M, 79228162.514264337589248983040M, 7.9228162514264337589248983040M, 
            79228162495817593524129366015M, 7922816249581759352412936601.5M, 7922816.2495817593524129366015M, 7.9228162495817593524129366015M, 
            79228162495817593519834398720M, 7922816249581759351983439872.0M, 792281.62495817593519834398720M, 7.9228162495817593519834398720M, 
            18446744073709551615M, 1844674407370955161.5M, 18446744073709551.615M, 184467440.73709551615M, 184.46744073709551615M, 1.8446744073709551615M, 
            18446744069414584320M, 1844674406941458432.0M, 18446744069414584.320M, 18446744.069414584320M, 184.46744069414584320M, 1.8446744069414584320M, 
            4294967295M, 429496729.5M, 42949672.95M, 42949.67295M, 42.94967295M, 4.294967295M, 
            1M, 1.0M, 1.00M, 1.000M, 1.0000000000M, 1.0000000000000000M, 1.00000000000000000000000M, 1.000000000000000000000000000M, 1.0000000000000000000000000000M,
            1.1M, 12.12M, 123.123M, 1234.1234M, 12345.12345M, 123456.123456M, 1234567.1234567M, 1234567890.1234567890M, 12345678901234.12345678901234M,
            99M, 9.9M, 99.99M, 999.999M, 9999.9999M, 99999.99999M, 999999.999999M, 9999999.9999999M, 99999999.99999999M, 999999999.999999999M, 9999999999.9999999999M, 
            9M, 0.9M, 0.99M, 0.999M, 0.9999M, 0.99999M, 0.999999M, 0.9999999M, 0.99999999M, 0.999999999M, 0.9999999999M, 0.99999999999999999999M, 
            new decimal (0, 0, 0, true, 0), new decimal (0, 0, 0, true, 1), new decimal (0, 0, 0, true, 2), new decimal (0, 0, 0, true, 14), new decimal (0, 0, 0, true, 27), new decimal (0, 0, 0, true, 28),
            2147483646M, 2147483646.00M, 2147483646.99M, 2147483646.999999999999999999M, 21474836.46M, 214.7483646M, 2.147483646M, 0.2147483646M, 0.0000000000000000002147483646M, 
            2147483647M, 2147483647.00M, 2147483647.99M, 2147483647.999999999999999999M, 21474836.47M, 214.7483647M, 2.147483647M, 0.2147483647M, 0.0000000000000000002147483647M, 
            2147483648M, 2147483648.00M, 2147483648.99M, 2147483648.999999999999999999M, 21474836.48M, 214.7483648M, 2.147483648M, 0.2147483648M, 0.0000000000000000002147483648M,
        };
        
        decimal[] result = new decimal[decimal_max.Length + numbers.Length + decimal_random.Length];
        
        decimal_max.CopyTo(result, 0);
        numbers.CopyTo(result, decimal_max.Length);
        decimal_random.CopyTo(result, decimal_max.Length + numbers.Length);

        /*var str = string.Join("\n", decimal_random);
        Console.WriteLine(str);*/
        
        float[] nums = {
            79228190848463234811415232512f,
            79228181403730269072124805120f,
            79228171958997303332834377728f,
            79228162514264337593543950336f,
            79228162514264337593543950335f,
            79228157791897854723898736640f,
            79228153069531371854253522944f,
            0.00000000000000000000000000025000003088542459379332304078347154134317722106936599f,
            0.00000000000000000000000000025000000681130028895287487758374725903158573934309539f,
            0.00000000000000000000000000024999998273717598411242671438402297671999425761682478f,
            0.00000000000000000000000000020000001267127752261443435102691509191874603599235749f,
            0.00000000000000000000000000020000000063421537019421026942705295076295029512922219f,
            0.00000000000000000000000000019999998859715321777398618782719080960715455426608689f,
            0.00000000000000000000000000015000001853125475627599382447008292480590633264161959f,
            0.00000000000000000000000000015000000649419260385576974287022078365011059177848429f,
            0.00000000000000000000000000014999999445713045143554566127035864249431485091534899f,
            0.00000000000000000000000000014999981390119816513218443727242652515737873796831947f,
            0.00000000000000000000000000010000001837270091372744125711331968711516875885931405f,
            0.00000000000000000000000000010000001235416983751732921631338861653727088842774640f,
            0.00000000000000000000000000010000000633563876130721717551345754595937301799617875f,
            0.00000000000000000000000000010000000031710768509710513471352647538147514756461109f,
            0.00000000000000000000000000009999999429857660888699309391359540480357727713304344f,
            0.00000000000000000000000000009999998828004553267688105311366433422567940670147579f,
            0.00000000000000000000000000009999998226151445646676901231373326364778153626990814f,
            0.00000000000000000000000000009000000028539691658739462124217382784332763280814999f,
            0.00000000000000000000000000005000000015855384254855256735676323769073757378230555f,
            0.00000000000000000000000000004999999714928830444349654695679770240178863856652172f,
        };
        
        foreach (float number in nums) {
            try {
                decimal tmp = Convert.ToDecimal(number);
                Console.WriteLine("{0:G9}", number);
                Console.WriteLine("{0}", number);
                Console.WriteLine("{0}", tmp);
                Console.WriteLine("{0}", BitConverter.SingleToInt32Bits(number));
                Console.WriteLine("");
            } catch (OverflowException e) {
                Console.WriteLine("{0:G9}", number);
                Console.WriteLine("{0}", number);
                Console.WriteLine("{0}", e.Message);
                Console.WriteLine("{0}", BitConverter.SingleToInt32Bits(number));
                Console.WriteLine("");
            }
        }
        Console.WriteLine("{0}", 70000000000000000000000000000M % 0.5M );
        
        /*float n1 = 79228101123500060288156172288f;
        float n2 = 79228162514264337593543950335f;
        float n3 = 79228157791897854723898736640f;
        Console.WriteLine("{0:G9}", n1);
        Console.WriteLine("{0}", Convert.ToDecimal(n1));
        Console.WriteLine("{0}", BitConverter.SingleToInt32Bits(n1));
        Console.WriteLine("");
        
        Console.WriteLine("{0:G9}", n2);
        try {
            Console.WriteLine("{0}", Convert.ToDecimal(n2));
        } catch {
            Console.WriteLine("Exception");
        }
        Console.WriteLine("{0}", BitConverter.SingleToInt32Bits(n2));
        Console.WriteLine("");
        Console.WriteLine("{0:G9}", n3);
        Console.WriteLine("{0}", Convert.ToDecimal(n3));
        Console.WriteLine("{0}", BitConverter.SingleToInt32Bits(n3));
        Console.WriteLine("");*/
        return;
        
        decimal[] tests_ok = new decimal[0];
        decimal[] tests_fail = new decimal[0];;
        
        
        foreach (decimal number in result) {
            Array.Resize(ref tests_ok, tests_ok.Length + 1);
            tests_ok[tests_ok.Length - 1] = number;
            decimal tmp = decimal.Negate(number);
            Array.Resize(ref tests_ok, tests_ok.Length + 1);
            tests_ok[tests_ok.Length - 1] = tmp;
        }

        Console.WriteLine("");
        Console.WriteLine("/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
        Console.WriteLine("Tests for correct data (automatic)");
        Console.WriteLine("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */");
        Console.WriteLine("");
        int i = 0;
        foreach (decimal number in tests_ok) {
            i++;
            Console.WriteLine("START_TEST(test_from_decimal_to_float_ok{0}) {{", i);
            ShowTestOk(number);
            Console.WriteLine("}");
            Console.WriteLine("");
        }

        //Console.WriteLine("");
        //Console.WriteLine("/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
        //Console.WriteLine("Tests for incorrect data (auto)");
        //Console.WriteLine("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */");
        //Console.WriteLine("");
        i = 0;
        foreach (decimal number in tests_fail) {
            i++;
            Console.WriteLine("START_TEST(test_from_decimal_to_float_fail{0}) {{", i);
            ShowTestFail(number);
            Console.WriteLine("}");
            Console.WriteLine("");
        }

        Console.WriteLine("");
        i = 0;
        int suit_num = 1;
        foreach (decimal number in tests_ok) {
            if (i % 400 == 0) {
                Console.WriteLine("Suite * from_decimal_to_float_suite{0}(void) {{", suit_num);
                Console.WriteLine("    Suite *s;");
                Console.WriteLine("    TCase *tc_core;");
                Console.WriteLine("");
                Console.WriteLine("    s = suite_create(\"debug{0}\");", suit_num);
                Console.WriteLine("    tc_core = tcase_create(\"Core\");");
                suit_num++;
            }
            i++;
            Console.WriteLine("    tcase_add_test(tc_core, test_from_decimal_to_float_ok{0});", i);
            if (i % 400 == 0) {
                Console.WriteLine("");
                Console.WriteLine("    suite_add_tcase(s, tc_core);");
                Console.WriteLine("    return s;");
                Console.WriteLine("}");
                Console.WriteLine("");
            }
        }
        
        if (i % 400 != 0) {
            Console.WriteLine("");
            Console.WriteLine("    suite_add_tcase(s, tc_core);");
            Console.WriteLine("    return s;");
            Console.WriteLine("}");
            Console.WriteLine("");
        }
        
        Console.WriteLine("");
        i = 0;
        foreach (decimal number in tests_fail) {
            if (i % 400 == 0) {
                Console.WriteLine("Suite * from_decimal_to_float_suite{0}(void) {{", suit_num);
                Console.WriteLine("    Suite *s;");
                Console.WriteLine("    TCase *tc_core;");
                Console.WriteLine("");
                Console.WriteLine("    s = suite_create(\"from_decimal_to_int{0}\");", suit_num);
                Console.WriteLine("    tc_core = tcase_create(\"Core\");");
                suit_num++;
            }
            i++;
            Console.WriteLine("    tcase_add_test(tc_core, test_from_decimal_to_float_fail{0});", i);
            if (i % 400 == 0) {
                Console.WriteLine("");
                Console.WriteLine("    suite_add_tcase(s, tc_core);");
                Console.WriteLine("    return s;");
                Console.WriteLine("}");
                Console.WriteLine("");
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
