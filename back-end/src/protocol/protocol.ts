import * as protobuf from 'protobufjs';
import * as path from 'path';

// Chargez tous les fichiers proto
const root = new protobuf.Root();
root.loadSync([
  path.join(__dirname, '../../../protocol/message_types.proto'),
  path.join(__dirname, '../../../protocol/message_envelope.proto'),
  path.join(__dirname, '../../../protocol/messages.proto')
]);

// Récupérez les types de messages
const MessageType = root.lookupEnum('gameprotocol.MessageType');
const MessageEnvelope = root.lookupType('gameprotocol.MessageEnvelope');
const MessageTypeMap: { [key: number]: string } = {
  [MessageType.values.MESSAGE_TYPE_HELLO]: 'gameprotocol.Hello',
  [MessageType.values.MESSAGE_TYPE_ADD_PLAYER]: 'gameprotocol.AddPlayer',
  [MessageType.values.MESSAGE_TYPE_GET_PLAYER_LIST]: 'gameprotocol.GetPlayerList',
  [MessageType.values.MESSAGE_TYPE_PLAYER_LIST]: 'gameprotocol.PlayerList',
};

// Fonction pour encoder un message
export function encodeMessage(type: number, payload: any): Buffer {
  // Trouvez le type de message correspondant
  const messageTypeName = MessageType.valuesById[type];
  if (!messageTypeName) {
    throw new Error(`Type de message inconnu: ${type}`);
  }
  const messageName = MessageTypeMap[type];
  if (!messageName) {
    throw new Error(`Type de message inconnu: ${type}`);
  }
  
  // Récupérez le type de message protobuf sans transformation
  const payloadType = root.lookupType(messageName);
  
  // Encodez le payload
  const payloadMessage = payloadType.create(payload);
  const payloadBuffer = payloadType.encode(payloadMessage).finish();
  
  // Créez l'enveloppe
  const envelope = {
    type: type,
    payload: payloadBuffer
  };
  
  // Encodez l'enveloppe
  return Buffer.from(MessageEnvelope.encode(envelope).finish());
}

// Fonction pour décoder un message
export function decodeMessage(buffer: Buffer): { type: number, payload: any } {
  // Décodez l'enveloppe
  const envelope = MessageEnvelope.decode(buffer);
  
  // Récupérez le type de message
  const messageTypeName = MessageType.valuesById[(envelope as any).type || envelope.$type];
  if (!messageTypeName) {
    throw new Error(`Type de message inconnu: ${(envelope as any).type || envelope.$type}`);
  }
  const messageName = MessageTypeMap[(envelope as any).type || envelope.$type];
  if (!messageName) {
    throw new Error(`Type de message inconnu: ${(envelope as any).type || envelope.$type}`);
  }
  
  // Même ici, pas besoin de transformation
  const payloadType = root.lookupType(messageName);
  
  // Décodez le payload
  const payload = payloadType.decode((envelope as any).payload) as any;
  
  return {
    type: (envelope as any).type,
    payload: payload.toJSON()
  };
}

// Exportez les types de messages pour faciliter l'utilisation
export const MessageTypes = MessageType.values;
