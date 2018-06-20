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
    /// Interaction logic for RoomDetailsWindow.xaml
    /// </summary>
    public partial class RoomDetailsWindow : Window
    {
        public RoomDetailsWindow(JsonResponsePacketDeserializer.RoomData data)
        {
            InitializeComponent();
            showDetails(data);
        }

        private void showDetails(JsonResponsePacketDeserializer.RoomData data)
        {
            this.RoomName.Text = data.name + " Details";
            this.RoomId.Text = data.id.ToString();
            this.PlayersNum.Text = data.maxPlayers.ToString();
            this.QuestionsNum.Text = data.questionCount.ToString();
            this.QuestionsTime.Text = data.timePerQuestion.ToString();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }
}
