/*
    Идем в онлайн-компилятор C# - https://www.onlinegdb.com/online_csharp_compiler
    Копируем весь код ниже и запускаем
*/



// Example of the decimal( int[ ] ) constructor.
using System;

class DecimalCtorIArrDemo
{
    // Get the exception type name; remove the namespace prefix.
    public static string GetExceptionType( Exception ex )
    {
        string exceptionType = ex.GetType( ).ToString( );
        return exceptionType.Substring(
            exceptionType.LastIndexOf( '.' ) + 1 );
    }

    // Create a decimal object and display its value.
    public static void CreateDecimal( int[ ] bits )
    {
        // Format the constructor for display.
        string ctor = String.Format(
            "decimal( {{ 0x{0:X}", bits[ 0 ] );
        string valOrExc;

        for( int index = 1; index < bits.Length; index++ )
            ctor += String.Format( ", 0x{0:X}", bits[ index ] );
        ctor += " } )";

        try
        {
            // Construct the decimal value.
            decimal decimalNum = new decimal( bits );

            // Format the decimal value for display.
            valOrExc = decimalNum.ToString( );
        }
        catch( Exception ex )
        {
            // Save the exception type if an exception was thrown.
            valOrExc = GetExceptionType( ex );
        }

        // Display the constructor and decimal value or exception.
        int ctorLen = 76 - valOrExc.Length;

        // Display the data on one line if it will fit.
        if( ctorLen > ctor.Length )
            Console.WriteLine( "{0}{1}", ctor.PadRight( ctorLen ),
                valOrExc );

        // Otherwise, display the data on two lines.
        else
        {
            Console.WriteLine( "{0}", ctor );
            Console.WriteLine( "{0,76}", valOrExc );
        }
    }

    public static void Main( )
    {
        Console.WriteLine(
            "This example of the decimal( int[ ] ) constructor " +
            "\ngenerates the following output.\n" );
        Console.WriteLine( "{0,-38}{1,38}", "Constructor",
            "Value or Exception" );
        Console.WriteLine( "{0,-38}{1,38}", "-----------",
            "------------------" );

        // Construct decimal objects from integer arrays.
        CreateDecimal( new int[ ] { 0, 0, 0, 0 } );
        CreateDecimal( new int[ ] { 1000000000, 0, 0, 0 } );
        CreateDecimal( new int[ ] { 0, 1000000000, 0, 0 } );
        CreateDecimal( new int[ ] { 0, 0, 1000000000, 0 } );
        CreateDecimal( new int[ ] { -1, -1, -1, 0 } );
        CreateDecimal( new int[ ] { -1, -1, -1, unchecked( (int)0x80000000 ) } );
        CreateDecimal( new int[ ] { -1, 0, 0, 0x1C0000 } );
        CreateDecimal( new int[ ] { -1, 0, 0, 0x100000 } );
        CreateDecimal( new int[ ] { -1, 0x0, 0x0, 0xA0000 } );
        CreateDecimal( new int[ ] { -1, 0x0, 0x0, 0x90000 } );
        CreateDecimal( new int[ ] { -1, 0x0, 0x0, -2146893824 } );
        CreateDecimal( new int[ ] { -1, 0x0, 0x0, 0x10000 } );
        CreateDecimal( new int[ ] { 0xF0000, 0xF0000, 0xF0000, 0xF0000 } );
        CreateDecimal( new int[ ] { 0, 0, 0, -2146893824 } );
        CreateDecimal( new int[ ] { 0, 0, 0, 0x1C0000 } );

        // ArgumentException:
        Console.WriteLine("\n\n");
        CreateDecimal( new int[ ] { 0, 0, 0 } );
        CreateDecimal( new int[ ] { 0, 0, 0, 0, 0 } );
        CreateDecimal( new int[ ] { 0, 0, 0, 1000000000 } );
        CreateDecimal( new int[ ] { -1, 0, 0, 0x1D0000 } ); 
        CreateDecimal( new int[ ] { 0, 0, 0, 0x1D0000 } );  
        CreateDecimal( new int[ ] { -1, 0, 0, 0x1C0001 } ); 
        CreateDecimal( new int[ ] { -1, 0, 0, 0x1C8000 } ); 
        CreateDecimal( new int[ ] { -1, 0, 0, 0x11C0000 } ); 
        CreateDecimal( new int[ ] { -1, 0, 0, 0x401C0000 } ); 
        
    }
}
