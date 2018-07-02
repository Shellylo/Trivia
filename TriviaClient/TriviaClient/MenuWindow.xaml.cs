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
    /// Interaction logic for MenuWindow.xaml
    /// </summary>
    public partial class MenuWindow : Window
    {
        private Client client;
        private bool isForcedClosing;

        public MenuWindow(Client client)
        {
            InitializeComponent();
            this.client = new Client(client);
            this.isForcedClosing = true;
        }

        private void JoinRoom_Click(object sender, RoutedEventArgs e)
        {
            this.isForcedClosing = false;
            JoinRoomWindow jrw = new JoinRoomWindow(this.client);
            this.Close();
            jrw.Show();
        }

        private void CreateRoom_Click(object sender, RoutedEventArgs e)
        {
            this.isForcedClosing = false;
            CreateRoomWindow crw = new CreateRoomWindow(this.client);
            this.Close();
            crw.Show();
        }

        private void Highscores_Click(object sender, RoutedEventArgs e)
        {
            this.isForcedClosing = false;
            HighscoresWindow hw = new HighscoresWindow(this.client);
            this.Close();
            hw.Show();
        }

        private void Signout_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                JsonResponsePacketDeserializer.LogoutResponse logoutResp = this.client.SendAndReceive<JsonResponsePacketDeserializer.LogoutResponse>(null, (uint)JsonRequestPacketSerializer.reqCodes.LOGOUT_REQ_CODE);
                if (logoutResp.status == 1)
                {
                    this.isForcedClosing = false;
                    MainWindow mw = new MainWindow(this.client);
                    this.Close();
                    mw.Show();
                }
                else
                {

                }
            }
            catch (Exception exception)
            {

            }
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if(this.isForcedClosing)
            {
                this.client.SendAndReceive<JsonResponsePacketDeserializer.LogoutResponse>(null, (uint)JsonRequestPacketSerializer.reqCodes.LOGOUT_REQ_CODE);
            }
        }
    }
}
