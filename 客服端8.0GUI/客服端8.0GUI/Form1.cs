using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net.Sockets;
using System.Net;
using System.Threading;
using System.IO;



namespace 客服端8._0GUI
{
    public partial class Form1 : Form

    {
        private byte[] result = new byte[1024 * 1024];
        private Socket ClientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

        public Form1()
        {
            InitializeComponent();
            TextBox.CheckForIllegalCrossThreadCalls = false;
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {
            ;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                //Thread.Sleep(2000);
                richTextBox1.Text += "向服务器发送消息:\r\n";
                richTextBox1.Text += textBox1.Text + "\r\n";
                string sb = textBox1.Text;
                string Client = ClientSocket.RemoteEndPoint.ToString();
                string SendMessage = "接收客户端" + Client + "消息：" + DateTime.Now + "\r\n" + sb + "\r\n";
                ClientSocket.Send(Encoding.UTF8.GetBytes(sb));
                textBox1.Clear();
            }
            catch (Exception ex)
            {
                richTextBox1.Text += "服务器可能已经关闭！\r\n";
                ClientSocket.Shutdown(SocketShutdown.Both);
                ClientSocket.Close();
            }
           
        }

        private void button2_Click(object sender, EventArgs e)
        {
            int Port = Convert.ToInt32(textBox3.Text);
            IPAddress IP = IPAddress.Parse((string)textBox2.Text);
            try
            {
                ClientSocket.Connect(new IPEndPoint(IP, Port));
                richTextBox2.Text += "连接服务器成功！\r\n";
                Thread thread = new Thread(ReceiveMessage);
                thread.IsBackground = true;
                thread.Start();
            }
            catch (Exception ex)
            {
                richTextBox2.Text += "连接服务器失败！\r\n";
                return;
            }
           
            
        }
        private void ReceiveMessage()
        {
            while (true)
            {
                try
                {
                    int ReceiveLength = ClientSocket.Receive(result);
                    richTextBox2.Text += "接收服务器消息：\r\n";
                    string str = Encoding.UTF8.GetString(result, 0, ReceiveLength) + "\r\n";
                    richTextBox2.Text += str;
                }
                catch (Exception ex)
                {
                    richTextBox2.Text += "接收消息失败！\r\n";
                    ClientSocket.Shutdown(SocketShutdown.Both);
                    ClientSocket.Close();
                    break;
                }
            }
        }

    }
}
