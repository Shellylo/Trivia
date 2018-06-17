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
using System.Windows.Threading;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for AdminRoomWindow.xaml
    /// </summary>
    public partial class AdminRoomWindow : Window
    {
        private Client client;
        private DispatcherTimer dt;

        public AdminRoomWindow(Client client, string roomName)
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

        private void Close_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                JsonResponsePacketDeserializer.CloseRoomResponse closeRoomResp = this.client.SendAndReceive<JsonResponsePacketDeserializer.CloseRoomResponse>(null, (uint)JsonRequestPacketSerializer.reqCodes.CLOSEROOM_REQ_CODE);
                if (closeRoomResp.status == 1)
                {
                    this.dt.Stop();
                    MenuWindow mw = new MenuWindow(this.client);
                    this.Close();
                    mw.Show();
                }
                else
                {
                    this.StartError.Visibility = Visibility.Hidden;
                    this.CloseError.Visibility = Visibility.Visible;
                }
            }
            catch (Exception exception)
            {

            }
        }

        private void Start_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                JsonResponsePacketDeserializer.StartGameResponse startGameResp = this.client.SendAndReceive<JsonResponsePacketDeserializer.StartGameResponse>(null, (uint)JsonRequestPacketSerializer.reqCodes.STARTGAME_REQ_CODE);
                if (startGameResp.status == 1)
                {
                    this.dt.Stop();
                    //GameWindow gw = new GameWindow(this.client);
                    //this.Close();
                    //gw.Show();
                }
                else
                {
                    this.CloseError.Visibility = Visibility.Hidden;
                    this.StartError.Visibility = Visibility.Visible;
                }
            }
            catch (Exception exception)
            {

            }
        }
    }
}
