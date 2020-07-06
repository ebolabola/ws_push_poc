using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using Common;
using Grpc.Core;
using interfaces;
using proto.PushService;
using PushPresenceService;

namespace PresenceService
{

    public class UserState
    {
        public int version;
        public int dummy;
        public PUSH_TOKEN tk;
    }

    public interface IPupindra
    {
        void AddUser(string userId, UserState st);
        void RemoveUser(string userId, PUSH_TOKEN tk);
        UserState GetState(string userId);
        void SetPushToken(string userId, PUSH_TOKEN tk);
    }
    public class Pupindra: IPupindra
    {
        Dictionary<string, UserState> users = new Dictionary<string, UserState>();
        private Task t_;
        PushQueue<PrescencePushData> _queue;
        public Pupindra(string connectionString)
        {
            _queue = new PushQueue<PrescencePushData>(connectionString,PushMessageType.PresenceService);

            t_ = Task.Run(async () =>
            {
                var tm = DateTime.Now;
                while (true)
                {
                    await Task.Delay(1000);
                    foreach (var st in users.Values)
                    {
                        st.dummy = DateTime.UtcNow.Second;
                        st.version += 1;
                        if (st.tk != null)
                        {
                            _queue.Enqueue(st.tk, new PrescencePushData() { Dummy = st.dummy, Version = st.version, Kuku = $"Kuku {DateTime.UtcNow}" });
                        }
                    }
                }
            });
        }
        public void AddUser(string userId, UserState st)
        {
            if (users.ContainsKey(userId))
            {
                users[userId] = st;
            }
            else
            {
                users.Add(userId, st);
            }
        }
        public void RemoveUser(string userId, PUSH_TOKEN tk)
        {
            users.Remove(userId);
        }

        public void SetPushToken(string userId, PUSH_TOKEN tk)
        {
            if (users.TryGetValue(userId, out var st))
            {
                st.tk = tk;
            }
        }
        public UserState GetState(string userId)
        {
            if (users.TryGetValue(userId, out var st))
            {
                return st;
            }
            return null;
        }
    }

    public class PresenceService : IPresenceService.IPresenceServiceBase
    {
        private IPupindra _pp;
        public PresenceService(IPupindra pp)
        {
            _pp = pp;
        }
        public override Task<PresenceState> PresenceConnect(PresenceConnectRequest request, ServerCallContext context)
        {
            _pp.AddUser(request.UserId, new UserState());
            var st = _pp.GetState(request.UserId);
            return Task.FromResult(new PresenceState() { Dummy = st.dummy, Version = st.version });
        }
        public override Task<PresenceState> PresenceGetStateAndSub(PresenceGetStateAndSubRequest request, ServerCallContext context)
        {
            _pp.SetPushToken(request.UserId, request.Token);
            var st = _pp.GetState(request.UserId);
            return Task.FromResult(new PresenceState() { Dummy = st.dummy, Version = st.version });
        }
    }
}
