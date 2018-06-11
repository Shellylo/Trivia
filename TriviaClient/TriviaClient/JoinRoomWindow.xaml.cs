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

        public JoinRoomWindow()
        {
            InitializeComponent();
            // get rooms from server
            UpdateRoomsToList();
        }

        private void UpdateRoomsToList()
        {
            // this.RoomsList.Items.Add()
        }

        private void Join_Click(object sender, RoutedEventArgs e)
        {
            // this.RoomsList.SelectedIndex // if nothing selected -1
        }

        private void Back_Click(object sender, RoutedEventArgs e)
        {
            MenuWindow mw = new MenuWindow(client);
            this.Close();
            mw.Show();
        }

        private void Refresh_Click(object sender, RoutedEventArgs e)
        {
            UpdateRoomsToList();
        }

        private void Details_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
