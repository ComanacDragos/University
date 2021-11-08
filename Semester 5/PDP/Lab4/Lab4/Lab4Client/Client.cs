using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace Lab4Client
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            using (Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Unspecified))
            {
                socket.Connect(IPAddress.Parse("192.168.0.115"), 7777);
                string a = Console.ReadLine();
                if (a == null)
                    a = "0";
                socket.Send(Encoding.ASCII.GetBytes(a));
                
                socket.Send(Encoding.ASCII.GetBytes(" "));
                string b = Console.ReadLine();
                if (b == null)
                    b = "0";
                socket.Send(Encoding.ASCII.GetBytes(b + "\n"));
                byte[] buffer =  new byte[10];
                int len = socket.Receive(buffer);
                Console.WriteLine(Encoding.Default.GetString(buffer));
            }
        }
    }
}