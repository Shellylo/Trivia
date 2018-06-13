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
        public bool[] variables;

        public CreateRoomWindow(Client client)
        {
            InitializeComponent();
            this.client = new Client(client);
            variables = new bool[4];
            for(int i = 0; i < variables.Length; i++)
            {
                variables[i] = false;
            }
        }

        private void Back_Click(object sender, RoutedEventArgs e)
        {
            MenuWindow mw = new MenuWindow(this.client);
            this.Close();
            mw.Show();
        }

        private void Create_Click(object sender, RoutedEventArgs e)
        {
            bool inputOk = true;
            for(int i = 0; i < variables.Length && inputOk; i++)
            {
                inputOk = inputOk && variables[i]; //
            }
            if(inputOk)
            {
                JsonRequestPacketSerializer.CreateRoomRequest createRoomReq = new JsonRequestPacketSerializer.CreateRoomRequest(this.NameBox.Text, UInt32.Parse(this.MaxPlayersBox.Text), UInt32.Parse(this.QuestionCountBox.Text), UInt32.Parse(this.QuestionTimeBox.Text));
                try
                {
                    JsonResponsePacketDeserializer.CreateRoomResponse createRoomResp = this.client.SendAndReceive<JsonResponsePacketDeserializer.CreateRoomResponse>(createRoomReq, (uint)JsonRequestPacketSerializer.reqCodes.CREATEROOM_REQ_CODE);
                    if (createRoomResp.status == 1)
                    {
                        //AdminRoomWindow arw = new AdminRoomWindow(this.client);
                        //this.Close();
                        //arw.Show();
                    }
                    else
                    {
                        this.VariablesError.Visibility = Visibility.Hidden;
                        this.CreateRoomError.Visibility = Visibility.Visible;
                    }
                }
                catch (Exception exception)
                {

                }
            }
            else
            {
                this.CreateRoomError.Visibility = Visibility.Hidden;
                this.VariablesError.Visibility = Visibility.Visible;
            }
        }

        private void NameBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            variables[0] = (this.NameBox.Text.Length > 0) && (Char.IsLetter(this.NameBox.Text[0])) && (this.NameBox.Text.All(c => Char.IsLetterOrDigit(c)));
            if(variables[0])
            {
                this.NameError.Visibility = Visibility.Hidden;
            }
            else
            {
                this.NameError.Visibility = Visibility.Visible;
            }
        }

        private void MaxPlayersBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            variables[1] = (this.MaxPlayersBox.Text.All(c => Char.IsDigit(c)) && this.MaxPlayersBox.Text.Length > 0);
            if (variables[1])
            {
                this.MaxPlayersError.Visibility = Visibility.Hidden;
            }
            else
            {
                this.MaxPlayersError.Visibility = Visibility.Visible;
            }
        }

        private void QuestionCountBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            variables[2] = (this.QuestionCountBox.Text.All(c => Char.IsDigit(c)) && this.QuestionCountBox.Text.Length > 0);
            if (variables[2])
            {
                this.QuestionCountError.Visibility = Visibility.Hidden;
            }
            else
            {
                this.QuestionCountError.Visibility = Visibility.Visible;
            }
        }

        private void QuestionTimeBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            variables[3] = (this.QuestionTimeBox.Text.All(c => Char.IsDigit(c)) && this.QuestionTimeBox.Text.Length > 0);
            if (variables[3])
            {
                this.QuestionTimeError.Visibility = Visibility.Hidden;
            }
            else
            {
                this.QuestionTimeError.Visibility = Visibility.Visible;
            }
        }
    }
}
