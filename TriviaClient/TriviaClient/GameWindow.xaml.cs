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
    /// Interaction logic for GameWindow.xaml
    /// </summary>
    public partial class GameWindow : Window
    {
        private Client client;
        private List<string> answers;

        public GameWindow(Client client)
        {
            InitializeComponent();
            this.client = new Client(client);
            JsonResponsePacketDeserializer.GetQuestionResponse questionResp = getQuestion();
            this.answers = questionResp.answers;
            updateScreen(questionResp.question);
            this.KeyDown += new KeyEventHandler(KeyPressed);
        }

        private void updateScreen(string question)
        {
            this.Question.Text = question;
            this.Answers.Children.Clear();
            for (int i = 0; i < this.answers.Count; i++)
            {
                TextBlock ans = new TextBlock();
                ans.Text = (i + 1) + ". " + answers[i];
                ans.FontSize = 15;
                ans.Height = 30;
                this.Answers.Children.Add(ans);
            }
        }

        private JsonResponsePacketDeserializer.GetQuestionResponse getQuestion()
        {
            try
            {
                return this.client.SendAndReceive<JsonResponsePacketDeserializer.GetQuestionResponse>(null, (uint)JsonRequestPacketSerializer.reqCodes.GETQUESTION_REQ_CODE);
            }
            catch (Exception exception)
            {

            }
            return new JsonResponsePacketDeserializer.GetQuestionResponse(0, "", new List<string>());
        }

        private void KeyPressed(Object sender, KeyEventArgs e)
        {
            string answer = "";
            switch (e.Key)
            {
                case Key.NumPad1:
                    answer = answers[0];
                    break;
                case Key.NumPad2:
                    answer = answers[1];
                    break;
                case Key.NumPad3:
                    answer = answers[2];
                    break;
                case Key.NumPad4:
                    answer = answers[3];
                    break;
            }
            JsonRequestPacketSerializer.SubmitAnswerRequest submitAnswerReq = new JsonRequestPacketSerializer.SubmitAnswerRequest(answer);
            try
            {
                JsonResponsePacketDeserializer.SubmitAnswerResponse submitAnswerResp = this.client.SendAndReceive<JsonResponsePacketDeserializer.SubmitAnswerResponse>(submitAnswerReq, (uint)JsonRequestPacketSerializer.reqCodes.SUBMITANSWER_REQ_CODE);
                if (submitAnswerResp.status == 1)
                {
                    if (submitAnswerResp.hasFinished)
                    {
                        //FinishGameWindow fgw = new FinishGameWindow(this.client);
                        //this.Close();
                        //fgw.Show();
                    }
                    JsonResponsePacketDeserializer.GetQuestionResponse questionResp = getQuestion();
                    this.answers = questionResp.answers;
                    updateScreen(questionResp.question);
                }
                else
                {

                }
            }
            catch (Exception exception)
            {

            }
        }

        private void Leave_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                JsonResponsePacketDeserializer.LeaveGameResponse leaveGameResp = this.client.SendAndReceive<JsonResponsePacketDeserializer.LeaveGameResponse>(null, (uint)JsonRequestPacketSerializer.reqCodes.LEAVEGAME_REQ_CODE);
                if (leaveGameResp.status == 1)
                {
                    MenuWindow mw = new MenuWindow(this.client);
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
