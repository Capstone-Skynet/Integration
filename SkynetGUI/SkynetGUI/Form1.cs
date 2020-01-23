using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
// Required
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Drawing;


namespace SkynetGUI
{
    public partial class Form1 : Form
    {
        TcpListener server = null;
        TcpClient client = null;
        
        Thread server_thread;
        Thread time_thread;
        
        public Form1()
        {
            InitializeComponent();
            StartListener();    // Begins listening for a connection once the program has begun
            StartTime();        // Begins the time

            status_label.Text = "SkynetGUI successfully loaded";
        }


        private void StartTime()
        {
            time_thread = new Thread(RunTime);
            time_thread.Start();
        }

        private void RunTime()
        {
            while (true)
            {
               status_time_label.Text  = "Time: " + DateTime.Now.ToString("h:mm:ss tt");
            }
        }

        /// <summary>
        /// SERVER RECEIVE DATA CODE BEGIN
        /// 
        /// code sourced from two example
        /// 1 > TcpListner Class example https://docs.microsoft.com/en-us/dotnet/api/system.net.sockets.tcplistener?redirectedfrom=MSDN&view=netframework-4.8
        /// 2 > Background Thread handler for TcpListner https://stackoverflow.com/questions/1738031/best-way-to-implement-socket-listener-in-c-sharp
        /// </summary>

        private void StartListener()
        {
            server_thread = new Thread(RunListener);
            server_thread.Start();
        }

        private void RunListener()
        {
            // Set the TcpListener on port 13000.
            Int32 port = 13000;
            IPAddress localAddr = IPAddress.Parse("127.0.0.1");

            // TcpListener server = new TcpListener(port);
            server = new TcpListener(localAddr, port);

            // Start listening for client requests.
            server.Start();

            while (true)
            {
                // Perform a blocking call to accept requests.
                // You could also user server.AcceptSocket() here.
                TcpClient client = server.AcceptTcpClient();
                
                // Control.Invoke updates the UI from the non UI thread
                this.Invoke(
                    new Action(
                        () =>
                        {
                            listBox1.Items.Add(string.Format("New connection from {0}", client.Client.RemoteEndPoint));
                            listbox_bottom_index();
                        }
                    ));
                ThreadPool.QueueUserWorkItem(ProcessClient, client);
                
            }
        }

        private void ProcessClient(object state)
        {
            client = state as TcpClient;

            // Buffer for reading data
            Byte[] bytes = new Byte[256];
            String data = null;

            data = null;

            // Get a stream object for reading and writing
            NetworkStream stream = client.GetStream();

            if (client.Connected)
            {
                try
                {
                    Image returnImage = Image.FromStream(stream);
                    this.Invoke(
                        new Action(
                            () =>
                            {
                                listBox1.Items.Add("Image sucessfully received");
                                listbox_bottom_index();
                            }
                        ));
                    main_image_box.Image = returnImage;
                }
                catch (SocketException e)
                {
                    Console.WriteLine("SocketException" + e);
                }
                catch (Exception e)
                {
                    
                }
            }
            
            int i;

            //// Loop to receive all the data sent by the client.
            //while ((i = stream.Read(bytes, 0, bytes.Length)) != 0)
            //{
            //    // Translate data bytes to a ASCII string.
            //    data = System.Text.Encoding.ASCII.GetString(bytes, 0, i);
            //    this.Invoke(
            //    new Action(
            //        () =>
            //        {
            //            listBox1.Items.Add("Received: " + data);
            //        }
            //    ));
                
            //    // Process the data sent by the client.
            //    data = data.ToUpper();

            //    byte[] msg = System.Text.Encoding.ASCII.GetBytes(data);

            //    // Send back a response.
            //    stream.Write(msg, 0, msg.Length);
            //    this.Invoke(
            //    new Action(
            //        () =>
            //        {
            //            listBox1.Items.Add("Sent: " + data);
            //        }
            //    ));
            //}
        }

        /// <summary>
        /// SERVER RECEIVE DATA CODE END
        /// </summary>


        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            // Stopping the threads
            server_thread.IsBackground = true;
            time_thread.IsBackground = true;
        }

        private void button_test_Click(object sender, EventArgs e)
        {
        }

        private void listbox_bottom_index()
        {
            listBox1.TopIndex = listBox1.Items.Count - 1;
        }
    }
}
