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
    /// Interaction logic for SignupWindow.xaml
    /// </summary>
    public partial class SignupWindow : Window
    {
        public Client client;

        public SignupWindow(Client client)
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

        private void UsernameTab_Down(object sender, KeyEventArgs e)
        {
            if ((!e.KeyboardDevice.IsKeyDown(Key.LeftShift)) && (!e.KeyboardDevice.IsKeyDown(Key.RightShift)) && e.KeyboardDevice.IsKeyDown(Key.Tab))
            {
                this.Password.Visibility = Visibility.Hidden;
                this.PasswordBox.Visibility = Visibility.Visible;
                this.PasswordBox.Focus();
                e.Handled = true;
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

        private void PasswordTab_Down(object sender, KeyEventArgs e)
        {
            if ((!e.KeyboardDevice.IsKeyDown(Key.LeftShift)) && (!e.KeyboardDevice.IsKeyDown(Key.RightShift)) && e.KeyboardDevice.IsKeyDown(Key.Tab))
            {
                this.Email.Text = "";
                this.Email.Foreground = Brushes.Black;
            }
        }

        public void Email_Down(object sender, MouseEventArgs e)
        {
            if (this.Email.Foreground == Brushes.LightGray)
            {
                this.Email.Text = "";
                this.Email.Foreground = Brushes.Black;
            }
        }

        private void Signup_Click(object sender, RoutedEventArgs e)
        {
            JsonRequestPacketSerializer.SignupRequest signupReq = new JsonRequestPacketSerializer.SignupRequest(this.Username.Text, this.PasswordBox.Password, this.Email.Text);
            try
            {
                JsonResponsePacketDeserializer.SignupResponse signupResp = this.client.SendAndReceive<JsonResponsePacketDeserializer.SignupResponse>(signupReq, (uint)JsonRequestPacketSerializer.reqCodes.SIGNUP_REQ_CODE);
                if (signupResp.status == 1)
                {
                    MainWindow mw = new MainWindow(this.client);
                    this.Close();
                    mw.Show();
                }
                else
                {
                    this.SignupError.Visibility = Visibility.Visible;
                }
            }
            catch (Exception exception)
            {
                
            }
        }

        private void Back_Click(object sender, RoutedEventArgs e)
        {
            MainWindow mw = new MainWindow(this.client);
            this.Close();
            mw.Show();
        }
    }
}
