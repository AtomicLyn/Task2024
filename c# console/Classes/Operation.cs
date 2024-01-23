using CSharpConsoleApplication.Interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharpConsoleApplication.Classes
{
    class Operation : IOperation
    {
        private Func<double[], double> function;
        private int argCount;

        public Operation(Func<double[], double> function, int argCount)
        {
            this.function = function;
            this.argCount = argCount;
        }

        public double Call(params double[] args)
        {
            if(args.Length >= argCount)
            {
                return function(args);
            }
            else
            {
                throw new ArgumentException("Not equal argument count.");
            }
        }
    }
}
