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
    class Client
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
    }
}
