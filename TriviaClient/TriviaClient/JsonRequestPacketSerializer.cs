using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace TriviaClient
{
    class JsonRequestPacketSerializer
    {
        public enum reqCodes : uint
        {
            LOGIN_REQ_CODE = 1,
            SIGNUP_REQ_CODE,
            LOGOUT_REQ_CODE,
            GETROOMS_REQ_CODE,
            GETPLAYERSROOM_REQ_CODE,
            JOINROOM_REQ_CODE,
            CREATEROOM_REQ_CODE,
            GETHIGHSCORES_REQ_CODE,
            CLOSEROOM_REQ_CODE,
            STARTGAME_REQ_CODE,
            GETROOMSTATE_REQ_CODE,
            LEAVEROOM_REQ_CODE,
            JOINGAME_REQ_CODE,
            GETQUESTION_REQ_CODE,
            SUBMITANSWER_REQ_CODE,
            GETGAMERESULTS_REQ_CODE,
            LEAVEGAME_REQ_CODE
        };

        public struct LoginRequest
        {
            public string username;
            public string password;

            public LoginRequest(string user, string pass)
            {
                this.username = user;
                this.password = pass;
            }
        };

        public struct SignupRequest
        {
            public string username;
            public string password;
            public string email;

            public SignupRequest(string user, string pass, string email)
            {
                this.username = user;
                this.password = pass;
                this.email = email;
            }
        };

        public struct GetPlayersInRoomRequest
        {
            public uint roomId;

            public GetPlayersInRoomRequest(uint id)
            {
                this.roomId = id;
            }
        };

        public struct JoinRoomRequest
        {
            public uint roomId;

            public JoinRoomRequest(uint id)
            {
                this.roomId = id;
            }
        };

        public struct CreateRoomRequest
        {
            public string name;
            public uint maxPlayers;
            public uint questionCount;
            public uint answerTimeout;

            public CreateRoomRequest(string name, uint maxPlayers, uint questionCount, uint answerTimeout)
            {
                this.name = name;
                this.maxPlayers = maxPlayers;
                this.questionCount = questionCount;
                this.answerTimeout = answerTimeout;
            }
        };

        public struct SubmitAnswerRequest
        {
            public string answer;

            public SubmitAnswerRequest(string answer)
            {
                this.answer = answer;
            }
        };

        public static byte[] createBuff(uint code)
        {
            byte[] lengthBuff = { 0, 0, 0, 0 };
            byte[] codeBuff = { Convert.ToByte((char)code) };
            return codeBuff.Concat(lengthBuff).ToArray();
        }

        public static byte[] createBuff(Object req, uint code)
        {
            string json = JsonConvert.SerializeObject(req);
            byte[] lengthBuff = BitConverter.GetBytes(json.Length);
            byte[] codeBuff = { Convert.ToByte((char)code) };
            return codeBuff.Concat(lengthBuff).Concat(new ASCIIEncoding().GetBytes(json)).ToArray();
        }
    }
}
