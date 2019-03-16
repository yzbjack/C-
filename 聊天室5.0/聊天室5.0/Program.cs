using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Text;
using System.Linq;
namespace Server
{
    class Program
    {
        public static void ListenConnection()
        {
            Socket ConnectionSocket = null;
            while (true)
            {
                try
                {
                    ConnectionSocket = ServerSocket.Accept();
                }
                catch (Exception ex)
                {
                    Console.WriteLine("监听套接字异常{0}", ex.Message);
                    break;
                }
                //获取客户端端口号和IP
                IPAddress ClientIP = (ConnectionSocket.RemoteEndPoint as IPEndPoint).Address;
                int ClientPort = (ConnectionSocket.RemoteEndPoint as IPEndPoint).Port;
                string SendMessage = "连接服务器成功\r\n" + "本地IP:" + ClientIP +
                    ",本地端口:" + ClientPort.ToString();
                //Console.WriteLine(SendMessage);
                ConnectionSocket.Send(Encoding.UTF8.GetBytes(SendMessage));
                string remotePoint = ConnectionSocket.RemoteEndPoint.ToString();
                Console.WriteLine("成功与客户端{0}建立连接!\t\n", remotePoint);
                ClientInformation.Add(remotePoint, ConnectionSocket);
                Thread thread = new Thread(ReceiveMessage);
                thread.IsBackground = true;
                thread.Start(ConnectionSocket);
            }
        }
        public static void ReceiveMessage(Object SocketClient)
        {
            Socket ReceiveSocket = (Socket)SocketClient;
            while (true)
            {
                byte[] result = new byte[1024 * 1024];
                try
                {
                    IPAddress ClientIP = (ReceiveSocket.RemoteEndPoint as IPEndPoint).Address;
                    int ClientPort = (ReceiveSocket.RemoteEndPoint as IPEndPoint).Port;
                    int ReceiveLength = ReceiveSocket.Receive(result);
                    string ReceiveMessage = Encoding.UTF8.GetString(result, 0, ReceiveLength);
                    Console.WriteLine("接收客户端:" + ReceiveSocket.RemoteEndPoint.ToString() +
                        "时间：" + DateTime.Now.ToString() + "\r\n" + "消息：" + ReceiveMessage + "\r\n\n");
                    foreach (string key in new List<string>(ClientInformation.Keys))
                    {
                        string s = ReceiveSocket.RemoteEndPoint.ToString();
                        if (key != s)
                        {
                            Socket socket = ClientInformation[key];
                            Console.WriteLine("向客户端{0}发送消息：", key);
                            socket.Send(Encoding.UTF8.GetBytes(ReceiveMessage));
                        }
                    }
                    //Console.WriteLine("向客户端{0}发送消息：", ReceiveSocket.RemoteEndPoint.ToString());
                    //string sb = Console.ReadLine();
                    //ReceiveSocket.Send(Encoding.UTF8.GetBytes(sb));
                }
                catch (Exception ex)
                {
                    Console.WriteLine("监听出现异常!!!");
                    Console.WriteLine("客户端" + ReceiveSocket.RemoteEndPoint + "已经连接中断" + "\r\n" +
                        ex.Message + "\r\n" + ex.StackTrace + "\r\n");
                    foreach (string key in new List<string>(ClientInformation.Keys))
                    {
                        string s = ReceiveSocket.RemoteEndPoint.ToString();
                        if (key.Equals(s))
                        {
                            ClientInformation.Remove(key);
                        }
                    }
                    ReceiveSocket.Shutdown(SocketShutdown.Both);
                    ReceiveSocket.Close();
                    break;
                }
            }
        }
        //private static byte[] result = new byte[1024];
        //List<Socket> list = new List<Socket>();
        static Dictionary<string, Socket> ClientInformation = new Dictionary<string, Socket> { };
        static Socket ServerSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        static void Main(String[] args)
        {
            try
            {
                int Port = 8899;
                IPAddress IP = IPAddress.Parse("127.0.0.1");
                ServerSocket.Bind(new IPEndPoint(IP, Port));
                ServerSocket.Listen(10);
                Console.WriteLine("启动监听成功！");
                Console.WriteLine("监听本地{0}成功", ServerSocket.LocalEndPoint.ToString());
                Thread ThreadListen = new Thread(ListenConnection);
                ThreadListen.IsBackground = true;
                ThreadListen.Start();
                Thread.Sleep(2000);
            }
            catch (Exception ex)
            {
                Console.WriteLine("监听异常!!!");
                ServerSocket.Shutdown(SocketShutdown.Both);
                ServerSocket.Close();
            }
            Console.ReadKey();
            Console.WriteLine("监听完毕，按任意键退出！");
        }
    }
}
//--------------------- 
//作者：童话ing
//来源：CSDN
//原文：https://blog.csdn.net/dl962454/article/details/78990735 
//版权声明：本文为博主原创文章，转载请附上博文链接！