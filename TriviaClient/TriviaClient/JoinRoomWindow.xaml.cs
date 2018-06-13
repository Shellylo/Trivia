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
    /// Interaction logic for JoinRoomWindow.xaml
    /// </summary>
    public partial class JoinRoomWindow : Window
    {
        public Client client;
        public List<JsonResponsePacketDeserializer.RoomData> rooms;

        public JoinRoomWindow(Client client)
        {
            InitializeComponent();
            this.client = new Client(client);
            rooms = new List<JsonResponsePacketDeserializer.RoomData>();
            // get rooms from server
            UpdateRoomsToList();
            UpdateListBox();
        }

        private void UpdateRoomsToList()
        {
            try
            {
                JsonResponsePacketDeserializer.GetRoomsResponse getRoomsResp = this.client.SendAndReceive<JsonResponsePacketDeserializer.GetRoomsResponse>(null, (uint)JsonRequestPacketSerializer.reqCodes.GETROOMS_REQ_CODE);
                if (getRoomsResp.status == 1)
                {
                    rooms = getRoomsResp.rooms;
                }
                else
                {
                    
                }
            }
            catch (Exception exception)
            {

            }
        }

        private void UpdateListBox()
        {
            this.RoomsList.Items.Clear();
            for(int i = 0; i < this.rooms.Count; i++)
            {
                Grid room = new Grid();
                room.Height = 30;
                room.Width = 525;
                switch (rooms[i].roomState)
                {
                    case 1:
                        room.Background = Brushes.LightGreen;
                        break;
                    case 2:
                        room.Background = Brushes.Red;
                        break;
                    case 3:
                        room.Background = Brushes.Gray;
                        break;
                }
                TextBlock roomName = new TextBlock();
                roomName.Text = rooms[i].name;
                roomName.Foreground = Brushes.White;
                roomName.FontSize = 15;
                roomName.FontWeight = FontWeights.Bold;
                roomName.HorizontalAlignment = HorizontalAlignment.Left;
                roomName.VerticalAlignment = VerticalAlignment.Center;
                room.Children.Add(roomName);
                this.RoomsList.Items.Add(room);
            }
        }

        private void Join_Click(object sender, RoutedEventArgs e)
        {
            if(this.RoomsList.SelectedIndex != -1) // if nothing selected -1
            {
                JsonRequestPacketSerializer.JoinRoomRequest joinRoomReq = new JsonRequestPacketSerializer.JoinRoomRequest(rooms[this.RoomsList.SelectedIndex].id);
                try
                {
                    JsonResponsePacketDeserializer.JoinRoomResponse joinRoomResp = this.client.SendAndReceive<JsonResponsePacketDeserializer.JoinRoomResponse>(joinRoomReq, (uint)JsonRequestPacketSerializer.reqCodes.JOINROOM_REQ_CODE);
                    if (joinRoomResp.status == 1)
                    {
                        //MemberRoomWindow mrw = new MemeberRoomWindow(this.client);
                        //this.Close();
                        //mrw.Show();
                    }
                    else
                    {
                        this.SelectRoomError.Visibility = Visibility.Hidden;
                        this.JoinRoomError.Visibility = Visibility.Visible;
                    }
                }
                catch (Exception exception)
                {

                }
            }
            else
            {
                this.JoinRoomError.Visibility = Visibility.Hidden;
                this.SelectRoomError.Visibility = Visibility.Visible;
            }
        }

        private void Back_Click(object sender, RoutedEventArgs e)
        {
            MenuWindow mw = new MenuWindow(this.client);
            this.Close();
            mw.Show();
        }

        private void Refresh_Click(object sender, RoutedEventArgs e)
        {
            UpdateRoomsToList();
            UpdateListBox();
        }
        
        private void Details_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
