using System;

namespace Common
{
    public interface ILogger
    {
        void LogInformation(string message, params object[] args);
        void LogError(string message, params object[] args);
    }

    public class Logger : ILogger
    {
        public void LogError(string message, params object[] args)
        {
            Console.WriteLine("[ERR:] " + message, args);
        }

        public static void LogError(Exception err, string additionalMessage)
        {
            Console.WriteLine("[ERR:] " + additionalMessage + ": " + err.ToString());
        }

        public void LogInformation(string message, params object[] args)
        {
            Console.WriteLine("[ERR:] " + message, args);
        }
    }
}