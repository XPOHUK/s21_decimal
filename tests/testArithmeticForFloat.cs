using System;
class test {
    static void Main() {
        decimal f = Decimal.Zero;
        decimal two = Decimal.Add(Decimal.One, Decimal.One);
        f = decimal.Add(f, s21_ipow(two, 30));
        f = decimal.Add(f, s21_ipow(two, 27));
        f = decimal.Add(f, s21_ipow(two, 24));
        f = decimal.Add(f, s21_ipow(two, 23));
        f = decimal.Add(f, s21_ipow(two, 20));
        f = decimal.Add(f, s21_ipow(two, 18));
        f = decimal.Add(f, s21_ipow(two, 17));
        f = decimal.Add(f, s21_ipow(two, 9));
        f = decimal.Add(f, s21_ipow(two, 8));
        
        Console.WriteLine("{0}", f); 
        // 1234567936
        
        f = Decimal.Zero;
        f = decimal.Add(f, s21_ipow(two, 89));
        f = decimal.Add(f, s21_ipow(two, 88));
        f = decimal.Add(f, s21_ipow(two, 87));
        f = decimal.Add(f, s21_ipow(two, 86));
        f = decimal.Add(f, s21_ipow(two, 85));
        f = decimal.Add(f, s21_ipow(two, 84));
        f = decimal.Add(f, s21_ipow(two, 83));
        f = decimal.Add(f, s21_ipow(two, 82));
        f = decimal.Add(f, s21_ipow(two, 80));
        f = decimal.Add(f, s21_ipow(two, 77));
        f = decimal.Add(f, s21_ipow(two, 76));
        f = decimal.Add(f, s21_ipow(two, 74));
        f = decimal.Add(f, s21_ipow(two, 72));
        f = decimal.Add(f, s21_ipow(two, 71));
        f = decimal.Add(f, s21_ipow(two, 70));
        f = decimal.Add(f, s21_ipow(two, 69));
        f = decimal.Add(f, s21_ipow(two, 67));
        f = decimal.Add(f, s21_ipow(two, 66));
        
        Console.WriteLine("{0}", f); 
        // 1234567900681729874025512960
        // 1234567900681729874025512960
        
        f = Decimal.Zero;
        f = decimal.Add(f, s21_ipow(two, 30));
        f = decimal.Add(f, s21_ipow(two, 27));
        f = decimal.Add(f, s21_ipow(two, 24));
        f = decimal.Add(f, s21_ipow(two, 23));
        f = decimal.Add(f, s21_ipow(two, 20));
        f = decimal.Add(f, s21_ipow(two, 18));
        f = decimal.Add(f, s21_ipow(two, 17));
        f = decimal.Add(f, s21_ipow(two, 8));
        f = decimal.Add(f, s21_ipow(two, 7));
        
        Console.WriteLine("{0}", f); 
        // 1234567552
        // 1234567552
        
        f = Decimal.Zero;
        f = decimal.Add(f, s21_ipow(two, 3));
        f = decimal.Add(f, s21_ipow(two, 1));
        f = decimal.Add(f, s21_ipow(two, -1));
        f = decimal.Add(f, s21_ipow(two, -2));
        f = decimal.Add(f, s21_ipow(two, -3));
        f = decimal.Add(f, s21_ipow(two, -4));
        f = decimal.Add(f, s21_ipow(two, -5));
        f = decimal.Add(f, s21_ipow(two, -7));
        f = decimal.Add(f, s21_ipow(two, -9));
        f = decimal.Add(f, s21_ipow(two, -10));
        f = decimal.Add(f, s21_ipow(two, -11));
        f = decimal.Add(f, s21_ipow(two, -12));
        f = decimal.Add(f, s21_ipow(two, -13));
        f = decimal.Add(f, s21_ipow(two, -17));
        f = decimal.Add(f, s21_ipow(two, -20));
        
        Console.WriteLine("{0}", f); 
        // 10.98035526275634765625
        // 10.98035526275634765625
        
        f = Decimal.Zero;
        f = decimal.Add(f, s21_ipow(two, -3));
        f = decimal.Add(f, s21_ipow(two, -5));
        
        Console.WriteLine("{0}", f); 
        // 0.15625
        // 0.15625
        
        /*f = Decimal.Zero;
        f = decimal.Add(f, s21_ipow(two, 96));
        f = decimal.Add(f, s21_ipow(two, 95));
        f = decimal.Add(f, s21_ipow(two, 91));
        f = decimal.Add(f, s21_ipow(two, 90));
        f = decimal.Add(f, s21_ipow(two, 89));
        f = decimal.Add(f, s21_ipow(two, 87));
        f = decimal.Add(f, s21_ipow(two, 86));
        f = decimal.Add(f, s21_ipow(two, 85));
        f = decimal.Add(f, s21_ipow(two, 83));
        f = decimal.Add(f, s21_ipow(two, 80));
        f = decimal.Add(f, s21_ipow(two, 76));
        
        Console.WriteLine("{0}", f);*/
        // 123456789182729271864492818432
        // System.OverflowException
        
        f = Decimal.Zero;
        f = decimal.Add(f, s21_ipow(two, 95));
        f = decimal.Add(f, s21_ipow(two, 94));
        f = decimal.Add(f, s21_ipow(two, 93));
        f = decimal.Add(f, s21_ipow(two, 92));
        f = decimal.Add(f, s21_ipow(two, 91));
        f = decimal.Add(f, s21_ipow(two, 90));
        f = decimal.Add(f, s21_ipow(two, 89));
        f = decimal.Add(f, s21_ipow(two, 88));
        f = decimal.Add(f, s21_ipow(two, 87));
        f = decimal.Add(f, s21_ipow(two, 86));
        f = decimal.Add(f, s21_ipow(two, 85));
        f = decimal.Add(f, s21_ipow(two, 84));
        f = decimal.Add(f, s21_ipow(two, 83));
        f = decimal.Add(f, s21_ipow(two, 82));
        f = decimal.Add(f, s21_ipow(two, 81));
        f = decimal.Add(f, s21_ipow(two, 80));
        f = decimal.Add(f, s21_ipow(two, 79));
        f = decimal.Add(f, s21_ipow(two, 78));
        f = decimal.Add(f, s21_ipow(two, 77));
        f = decimal.Add(f, s21_ipow(two, 76));
        f = decimal.Add(f, s21_ipow(two, 73));
        f = decimal.Add(f, s21_ipow(two, 72));
        Console.WriteLine("{0}", f);
        // 79228101123500060288156172288
        // 79228101123500060288156172288
    }
    
    public static decimal s21_ipow(decimal value, int exp) {
        decimal result;
    
        if (exp == 0) {
            result = Decimal.One;
        } else if (exp < 0) {
            result = decimal.Divide(Decimal.One, s21_ipow(value, -exp));
        } else {
            result = decimal.Multiply(value, s21_ipow(value, exp - 1));
        }
    
        return result;
    }

}
