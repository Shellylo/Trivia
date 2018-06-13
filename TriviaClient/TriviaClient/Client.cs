using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Net;

/*
    using Newtonsoft.Json; (include Json)
    string json = JsonConvert.SerializeObject(Object); (serialize - can be any Object)
    Object obj = JsonConvert.DeserializeObject<Object>(string); (deserialize - can be any Object)

    byte[] buffer = new ASCIIEncoding().GetBytes(string); (string to byte[])
    string str = new ASCIIEncoding().GetString(buffer); (byte[] to string)

    clientStream.Read(buffer (byte[]), offset (int), length (int));
    clientStream.Write(buffer (byte[]), offset (int), length (int));
*/

namespace TriviaClient
{
    public class Client
    {
        private NetworkStream clientStream;

        public Client()
        {
            Connect("127.0.0.1", 2431);
        }

        public Client(Client other)
        {
            this.clientStream = other.clientStream;
        }

        public void Connect(string serverIP, int port)
        {
            TcpClient client = new TcpClient();
            IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse(serverIP), port);
            client.Connect(serverEndPoint);
            this.clientStream = client.GetStream();
        }

        public T SendAndReceive<T>(Object req, uint code)
        {
            byte[] send;
            if(req != null)
            {
                send = JsonRequestPacketSerializer.createBuff(req, code);
            }
            else
            {
                send = JsonRequestPacketSerializer.createBuff(code);
            }
            //Console.WriteLine(new ASCIIEncoding().GetString(send).Length);
            this.clientStream.Write(send, 0, send.Length);
            byte[] recvCodeBuff = new byte[1];
            byte[] recvLengthBuff = new byte[4];
            this.clientStream.Read(recvCodeBuff, 0, 1);
            this.clientStream.Read(recvLengthBuff, 0, 4);   
            uint recvCode = Convert.ToUInt32(recvCodeBuff[0]);
            uint recvLength = BitConverter.ToUInt32(recvLengthBuff, 0);
            if(recvCode != code)
            {
                this.clientStream.Flush();
                throw new Exception("Request is not relevant");
            }
            byte[] recvDataBuff = new byte[recvLength];
            this.clientStream.Read(recvDataBuff, 0, (int)recvLength);
            return JsonResponsePacketDeserializer.createStruct<T>(recvDataBuff);            
        }
    }
}
