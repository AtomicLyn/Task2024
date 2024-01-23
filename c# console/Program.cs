using CSharpConsoleApplication.Classes;
using CSharpConsoleApplication.Interfaces;
using System;

namespace CSharpConsoleApplication
{
    class Program
    {
        static void Main(string[] args)
        {
            IExecution execution = new Executor();

            bool exitStatus = false;

            while (!exitStatus)
            {
                Console.WriteLine("----------------------------------");
                Console.WriteLine("2> +,-,*,/,pow");
                Console.WriteLine("1> sin,cos,tg,ctg,sqrt,abs");
                Console.WriteLine("0> q");

                Console.Write("op: ");
                string opStr = Console.ReadLine().ToLower();
                if(opStr == "q")
                {
                    exitStatus = true;
                    break;
                }

                Console.Write("args: ");
                string argsStr = Console.ReadLine();

                try
                {
                    double result = execution.Execute(opStr, argsStr);
                    Console.WriteLine($"\nresult: {result}");
                }
                catch(ArgumentException ex)
                {
                    Console.WriteLine($"\nerror: {ex.Message}");
                }
            }
        }
    }
}
