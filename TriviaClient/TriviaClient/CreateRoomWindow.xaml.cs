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
    /// Interaction logic for CreateRoomWindow.xaml
    /// </summary>
    public partial class CreateRoomWindow : Window
    {
        public Client client;

        public CreateRoomWindow(Client client)
        {
            InitializeComponent();
            this.client = new Client(client);
        }

        private void Back_Click(object sender, RoutedEventArgs e)
        {
            MenuWindow mw = new MenuWindow(this.client);
            this.Close();
            mw.Show();
        }

        private void Create_Click(object sender, RoutedEventArgs e)
        {

        }

        private void NameBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private void MaxPlayersBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private void QuestionCountBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private void QuestionTimeBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }
    }
}
