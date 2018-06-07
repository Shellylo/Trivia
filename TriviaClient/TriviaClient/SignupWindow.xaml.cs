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
        public SignupWindow()
        {
            InitializeComponent();
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

        }

        private void Back_Click(object sender, RoutedEventArgs e)
        {
            MainWindow mw = new MainWindow();
            this.Close();
            mw.Show();
        }
    }
}
