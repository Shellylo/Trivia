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
using System.Windows.Navigation;
using System.Windows.Shapes;
using Newtonsoft.Json;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private Client client;

        public MainWindow()
        {
            InitializeComponent();
            this.client = new Client();
        }

        public MainWindow(Client client)
        {
            InitializeComponent();
            this.client = new Client(client);
        }

        private void Username_Down(object sender, MouseEventArgs e)
        {
            if (this.Username.Foreground == Brushes.LightGray)
            {
                this.Username.Text = "";
                this.Username.Foreground = Brushes.Black;
            }
        }

        private void Password_Down(object sender, MouseEventArgs e)
        {
            if (this.Password.Foreground == Brushes.LightGray)
            {
                this.Password.Visibility = Visibility.Hidden;
                this.PasswordBox.Visibility = Visibility.Visible;
                this.PasswordBox.Focus();
            }
        }

        private void Login_Click(object sender, RoutedEventArgs e)
        {
            JsonRequestPacketSerializer.LoginRequest loginReq = new JsonRequestPacketSerializer.LoginRequest(this.Username.Text, this.PasswordBox.Password);
            try
            {
                JsonResponsePacketDeserializer.LoginResponse loginResp = this.client.SendAndReceive<JsonResponsePacketDeserializer.LoginResponse>(loginReq, (uint)JsonRequestPacketSerializer.reqCodes.LOGIN_REQ_CODE);
                if (loginResp.status == 1)
                {
                    MenuWindow mw = new MenuWindow(this.client);
                    this.Close();
                    mw.Show();
                }
                else
                {
                    LoginError.Visibility = Visibility.Visible;
                }
            }
            catch(Exception exception)
            {

            }
        }

        private void Signup_Click(object sender, RoutedEventArgs e)
        {
            SignupWindow sw = new SignupWindow(client);
            this.Close();
            sw.Show();
        }
    }
}
