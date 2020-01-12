using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.Drawing;
using System.IO;
using System.Threading;

namespace ConsoleApp2
{
    class Program
    {

        static void Main(string[] args)
        {
            Connect("127.0.0.1", "hello there");
        }

        static void Connect(String server, String message)
        {
            try
            {
                // Create a TcpClient.
                // Note, for this client to work you need to have a TcpServer 
                // connected to the same address as specified by the server, port
                // combination.
                Int32 port = 13000;
                TcpClient client = new TcpClient(server, port);

                // Get a client stream for reading and writing.
                //  Stream stream = client.GetStream();



                ///////////////////////////////////////////////////////////////////////////
                NetworkStream stream = null;
                while (true)
                {
                    for (int i = 1; i <= 10; i++)
                    {
                        client = new TcpClient(server, port);
                        stream = client.GetStream();
                        string filename = "../../" + i.ToString() + ".jpg";

                        Console.WriteLine("Preparing image to send . . .");
                        Bitmap sent_image = new Bitmap(filename, true);
                        MemoryStream mMemoryStream = new MemoryStream();
                        sent_image.Save(mMemoryStream, System.Drawing.Imaging.ImageFormat.Png);
                        byte[] bstream = mMemoryStream.ToArray();

                        NetworkStream nstream = client.GetStream();

                        Console.WriteLine("Sending the image " + i.ToString() + ".jpg now . . . ");
                        nstream.Write(bstream, 0, bstream.Length);
                        Thread.Sleep(100);
                        stream.Close();
                        client.Close();
                    }
                }

                //Console.WriteLine("Preparing image to send . . .");
                //Bitmap sent_image = new Bitmap("../../1.jpg", true);
                //MemoryStream mMemoryStream = new MemoryStream();
                //sent_image.Save(mMemoryStream, System.Drawing.Imaging.ImageFormat.Png);
                //byte[] bstream = mMemoryStream.ToArray();

                //NetworkStream nstream = client.GetStream();

                //Console.WriteLine("Sending the image 1.jpg now . . . ");
                //nstream.Write(bstream, 0, bstream.Length);
                //Thread.Sleep(500);

                ///////////////////////////////////////////////////////////////////////////////////

                //// Translate the passed message into ASCII and store it as a Byte array.
                //Byte[] data = System.Text.Encoding.ASCII.GetBytes(message);
                //// Send the message to the connected TcpServer. 
                //stream.Write(data, 0, data.Length);

                //Console.WriteLine("Sent: {0}", message);

                //// Receive the TcpServer.response.

                //// Buffer to store the response bytes.
                //data = new Byte[256];

                //// String to store the response ASCII representation.
                //String responseData = String.Empty;

                //// Read the first batch of the TcpServer response bytes.
                //Int32 bytes = stream.Read(data, 0, data.Length);
                //responseData = System.Text.Encoding.ASCII.GetString(data, 0, bytes);
                //Console.WriteLine("Received: {0}", responseData);

                // Close everything.
                stream.Close();
                client.Close();
            }
            catch (ArgumentNullException e)
            {
                Console.WriteLine("ArgumentNullException: {0}", e);
            }
            catch (SocketException e)
            {
                Console.WriteLine("SocketException: {0}", e);
            }
            catch (IOException e)
            {
                Console.WriteLine("IOException: {0}", e);
            }

            Console.WriteLine("\n Press Enter to continue...");
            Console.Read();
        }
    }
}
