using System;
using System.Text;
using System.Net.Sockets;
using System.Net;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Collections.Generic;
using System.IO;
using System.Threading;


namespace Lab4
{
    public class CallbackParser
    {
        class Session
        {
            enum State {ReadingHeaders, ReadingBody}

            private string _filePath;
            
            private Socket _conn;
            private byte[] _buffer;
            private FileStream _fileStream;
            private string _headers = "";
            private State _state = State.ReadingHeaders;
            private int remainingBytes = -1;
            public void Log(string message)
            {
                Console.WriteLine($"Callback: {message} {_filePath.Substring(_filePath.LastIndexOf("\\") + 1)} {Thread.CurrentThread.ManagedThreadId}");
            }
            public Session(Socket conn, string filePath) {
                _conn = conn;
                _buffer = new byte[1024];
                _filePath = "E:\\University\\Semester 5\\PDP\\Lab4\\Lab4\\Lab4\\downloads\\callback\\" + filePath + ".txt";
                _fileStream = File.Create(_filePath);
            }

            public void Start(IPAddress ipAddress, string request)
            {
                Log($"starting {_filePath}");
                
                _conn.BeginConnect(new IPEndPoint(ipAddress, 80), ar =>
                {
                    Log("Begin connect");
                    _conn.BeginSend(Encoding.ASCII.GetBytes(request), 0, request.Length, SocketFlags.None, aRes =>
                    {
                        Log("Begin sending");
                        int result = _conn.EndSend(aRes);
                        Log($"End send {result}");
                        _conn.BeginReceive(_buffer, 0, _buffer.Length, SocketFlags.None, OnBytesReceived, null);
                    }, null);
                    
                    Log($"Waiting...{_conn.Connected}");
                    while(_conn.Connected)
                        Thread.Sleep(100);
                }, null);
            }

            private void OnBytesReceived(IAsyncResult ar) {
                Log("On bytes received");
                var size = _conn.EndReceive(ar);
                Log($"Received {size}");
                if (size.Equals(0))
                {
                    if(remainingBytes>0)
                        Log("Closing early... did not finish downloading");
                    else
                        Log("Closing...");
                    _conn.Close();
                    _fileStream.Close();
                    return;
                }
                string output = Encoding.Default.GetString(_buffer).Substring(0, size);
                //Log(output);

                switch (_state)
                {
                    case State.ReadingHeaders:
                        _headers += output;
                        if (_headers.Contains("\r\n\r\n"))
                        {
                            int index = _headers.IndexOf("\r\n\r\n");
                            string headers = _headers.Substring(0, index);
                            string body = _headers.Substring(index + 4);
                            
                            var regex = new Regex("Content-Length: \\d+");

                            string matched = regex.Match(headers).Value;
                            if (matched.Length.Equals(0))
                            {
                                Log("Length header not present...exiting");
                                _conn.Close();
                                _fileStream.Close();
                                return;
                            }
                            remainingBytes = int.Parse(matched.Substring(16)) - body.Length;
                            _state = State.ReadingBody;
                            _fileStream.BeginWrite(Encoding.ASCII.GetBytes(body), 0, body.Length, result =>
                            {
                                _fileStream.EndWrite(result);
                            }, null);
                        }
                        break;
                    case State.ReadingBody:
                        remainingBytes -= output.Length;
                        _fileStream.BeginWrite(Encoding.ASCII.GetBytes(output), 0, output.Length, result =>
                        {
                            _fileStream.EndWrite(result);
                        }, null);
                        break;
                }
                
                _conn.BeginReceive(_buffer, 0, _buffer.Length, SocketFlags.None, OnBytesReceived, null);
            }
        }
        public CallbackParser(List<string> urls)
        {
            foreach(var url in urls)
            {
                int slashIndex = url.IndexOf("/");
                string host = slashIndex.Equals(-1) ? url : url.Substring(0, slashIndex);
                string resource = slashIndex.Equals(-1) ? "/" : url.Substring(slashIndex);
            
                var ipAddress = Dns.GetHostEntry(host).AddressList[0];
                Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Unspecified);
                
                var session = new Session(socket, resource.Substring(resource.LastIndexOf("/")+1));
                session.Start(ipAddress,$"GET {resource} HTTP/1.1\r\n" +
                                               $"Host: {host}\r\n" +
                                               $"Content-Length: 0\r\n\r\n");
            }
            Thread.Sleep(1000);
        }
    }
    
}