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

        public MenuWindow(Client client)
        {
            InitializeComponent();
            this.client = new Client(client);
        }

        private void JoinRoom_Click(object sender, RoutedEventArgs e)
        {
            JoinRoomWindow jrw = new JoinRoomWindow();
            this.Close();
            jrw.Show();
        }

        private void CreateRoom_Click(object sender, RoutedEventArgs e)
        {
            CreateRoomWindow crw = new CreateRoomWindow();
            this.Close();
            crw.Show();
        }

        private void Highscores_Click(object sender, RoutedEventArgs e)
        {
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
    }
}
