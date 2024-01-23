using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CSharpConsoleApplication.Interfaces;

namespace CSharpConsoleApplication.Classes
{
    class Executor : IExecution
    {
        private IDictionary<string, IOperation> funcDictionary;

        public Executor()
        {
            funcDictionary = new Dictionary<string, IOperation>()
            {
                { "+", new Operation(arr => arr[0] + arr[1], 2) },
                { "-", new Operation(arr => arr[0] - arr[1], 2) },
                { "*", new Operation(arr => arr[0] * arr[1], 2) },
                { "/", new Operation(arr => arr[0] / arr[1], 2) },
                { "pow", new Operation(arr => Math.Pow(arr[0], arr[1]), 2) },
                { "sin", new Operation(arr => Math.Sin(arr.First()), 1) },
                { "cos", new Operation(arr => Math.Cos(arr.First()), 1) },
                { "tg", new Operation(arr => Math.Tan(arr.First()), 1) },
                { "ctg", new Operation(arr => Math.Cos(arr.First()) / Math.Sin(arr.First()), 1) },
                { "sqrt", new Operation(arr => Math.Sqrt(arr.First()), 1) },
                { "abs", new Operation(arr => Math.Abs(arr.First()), 1) }
            };
        }

        double[] ToArgs(string args)
        {
            string[] argsSplit = args.Split(" ");
            List<double> argsResult = new List<double>();
            foreach(string arg in argsSplit)
            {
                try {
                    argsResult.Add(Convert.ToDouble(arg));
                }
                catch { }
            }
            return argsResult.ToArray();
            
        }
        public double Execute(string opStr, string argsStr)
        {
            double[] args = ToArgs(argsStr);

            if (!funcDictionary.ContainsKey(opStr)) throw new ArgumentException("Operation not found.");

            return funcDictionary[opStr].Call(args);
        }
    }
}
