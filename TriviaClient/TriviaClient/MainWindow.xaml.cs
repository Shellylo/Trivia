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

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
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

        private void Login_Click(object sender, RoutedEventArgs e)
        {
            MenuWindow mw = new MenuWindow();
            this.Close();
            mw.Show();
        }

        private void Signup_Click(object sender, RoutedEventArgs e)
        {
            SignupWindow sw = new SignupWindow();
            this.Close();
            sw.Show();
        }
    }
}
