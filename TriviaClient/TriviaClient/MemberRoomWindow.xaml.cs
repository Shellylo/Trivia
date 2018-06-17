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
using System.Threading;
using System.Windows.Threading;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for MemberRoomWindow.xaml
    /// </summary>
    public partial class MemberRoomWindow : Window
    {
        private Client client;
        private DispatcherTimer dt;

        public MemberRoomWindow(Client client, string roomName)
        {
            InitializeComponent();
            this.client = new Client(client);
            this.RoomName.Text = roomName;
            //   Thread t = new Thread();
            //    t.Start(roomName);
            this.dt = new DispatcherTimer();
            this.dt.Tick += ShowRoomDetails;
            this.dt.Interval = new TimeSpan(0, 0, 1);
            this.dt.Start();
        }

        private void ShowRoomDetails(Object sender, EventArgs e)
        { 
            try
            {
                JsonResponsePacketDeserializer.GetRoomStateResponse roomStateResp = this.client.SendAndReceive<JsonResponsePacketDeserializer.GetRoomStateResponse>(null, (uint)JsonRequestPacketSerializer.reqCodes.GETROOMSTATE_REQ_CODE);
                if (roomStateResp.status == 1)
                {
                    if (roomStateResp.roomStatus == 2) // closed
                    {
                        LeaveRoom();
                    }
                    else if (roomStateResp.roomStatus == 3) // started
                    {
                        JoinGame();
                    }
                    if (this.QuestionsNum.Text == "")
                    {
                        this.QuestionsNum.Text = "Questions: " + roomStateResp.questionCount.ToString();
                    }
                    if (this.QuestionsTime.Text == "")
                    {
                        this.QuestionsTime.Text = "Timeout: " + roomStateResp.answerTimeout.ToString();
                    }
                    this.PlayersList.Children.Clear();
                    for (int i = 0; i < roomStateResp.players.Count; i++)
                    {
                        TextBlock playerName = new TextBlock();
                        playerName.Text = roomStateResp.players[i];
                        playerName.FontSize = 20;
                        playerName.HorizontalAlignment = HorizontalAlignment.Left;
                        playerName.VerticalAlignment = VerticalAlignment.Center;
                        playerName.Height = 30;
                        playerName.Width = 525;
                        this.PlayersList.Children.Add(playerName);
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
        
        private void LeaveRoom()
        {
            JsonResponsePacketDeserializer.LeaveRoomResponse leaveRoomResp = this.client.SendAndReceive<JsonResponsePacketDeserializer.LeaveRoomResponse>(null, (uint)JsonRequestPacketSerializer.reqCodes.LEAVEROOM_REQ_CODE);
            if (leaveRoomResp.status == 1)
            {
                this.dt.Stop();
                MenuWindow mw = new MenuWindow(this.client);
                this.Close();
                mw.Show();
            }
            else
            {
                this.LeaveError.Visibility = Visibility.Visible;
            }
        }

        private void JoinGame()
        {
            JsonResponsePacketDeserializer.JoinGameResponse joinGameResp = this.client.SendAndReceive<JsonResponsePacketDeserializer.JoinGameResponse>(null, (uint)JsonRequestPacketSerializer.reqCodes.JOINGAME_REQ_CODE);
            if (joinGameResp.status == 1)
            {
                this.dt.Stop();
                GameWindow gw = new GameWindow(this.client);
                this.Close();
                gw.Show();
            }
            else
            {

            }
        }

        private void Leave_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                LeaveRoom();
            }
            catch (Exception exception)
            {

            }
        }
    }
}
