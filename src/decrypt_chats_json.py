from olm import InboundGroupSession
import json
import sys

session_key_json_path = sys.argv[1]
chat_json_path = sys.argv[2]

with open(session_key_json_path) as f:
    key_data = json.load(f)
    sessions = {item["session_id"]: InboundGroupSession.import_session(
        item["session_key"]) for item in key_data}

with open(chat_json_path) as f:
    enc_data = json.load(f)
    decr_messages = [json.loads(sessions[enc_chunk["content"]["session_id"]].decrypt(enc_chunk["content"]["ciphertext"])[0]) for enc_chunk in (chunk for chunk in enc_data["chunk"] if enc_data["chunk"]["type"] == "m.room.encrypted")]

print(decr_messages)  # TODO: to json
