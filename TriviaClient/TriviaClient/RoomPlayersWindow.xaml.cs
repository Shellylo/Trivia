using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for RoomPlayersWindow.xaml
    /// </summary>
    public partial class RoomPlayersWindow : Window
    {
        private Client client;

        public RoomPlayersWindow(Client client, JsonResponsePacketDeserializer.RoomData data)
        {
            InitializeComponent();
            this.client = new Client(client);
            showDetails(data);
        }

        private void showDetails(JsonResponsePacketDeserializer.RoomData data)
        {
            this.RoomName.Text = data.name + " Players";
            JsonRequestPacketSerializer.GetPlayersInRoomRequest getPlayersInRoomReq = new JsonRequestPacketSerializer.GetPlayersInRoomRequest(data.id);
            try
            {
                JsonResponsePacketDeserializer.GetPlayersInRoomResponse getPlayersInRoomResp = this.client.SendAndReceive<JsonResponsePacketDeserializer.GetPlayersInRoomResponse>(getPlayersInRoomReq, (uint)JsonRequestPacketSerializer.reqCodes.GETPLAYERSROOM_REQ_CODE);
                if (getPlayersInRoomResp.status == 1)
                {
                    this.Players.Children.Clear();
                    for (int i = 0; i < getPlayersInRoomResp.users.Count; i++)
                    {
                        TextBlock playerName = new TextBlock();
                        playerName.Text = getPlayersInRoomResp.users[i];
                        playerName.FontSize = 20;
                        playerName.HorizontalAlignment = HorizontalAlignment.Left;
                        playerName.VerticalAlignment = VerticalAlignment.Center;
                        playerName.Height = 30;
                        playerName.Width = 525;
                        this.Players.Children.Add(playerName);
                    }
                }
                else
                {
                    
                }
            }
            catch (Exception exception)
            {

            }
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }
}
