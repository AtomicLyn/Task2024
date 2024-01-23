using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharpConsoleApplication.Interfaces
{
    interface IOperation
    {
        double Call(params double[] args);
    }
}
