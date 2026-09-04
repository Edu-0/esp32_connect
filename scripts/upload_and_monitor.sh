#!/usr/bin/env bash
set -euo pipefail

# Passa o BUSID como argumento se for diferente de 1-2, ex: ./upload_and_monitor.sh 2-4
BUSID="${1:-1-2}"

USBIPD="/mnt/c/Program Files/usbipd-win/usbipd.exe"
POWERSHELL="/mnt/c/Windows/System32/WindowsPowerShell/v1.0/powershell.exe"

cd "$(dirname "$0")/.."

# usbipd list mostra "Not shared" quando o dispositivo ainda nao foi vinculado no Windows.
if "$USBIPD" list | grep -q "^${BUSID}.*Not shared"; then
  echo "Vinculando ${BUSID} no Windows (pedira permissao de administrador)..."
  "$POWERSHELL" -Command "Start-Process usbipd -ArgumentList 'bind --busid ${BUSID} --force' -Verb RunAs -Wait"
fi

echo "Anexando ${BUSID} ao WSL..."
if "$USBIPD" list | grep -q "^${BUSID}.*Attached"; then
  echo "${BUSID} ja esta anexado ao WSL."
else
  "$USBIPD" attach --wsl --busid "${BUSID}"
fi

pio run --target upload

CSV_FILE="scripts/connected_macs.csv"
MONITOR_LOG="$(mktemp)"
trap 'rm -f "$MONITOR_LOG"' EXIT

# Ctrl+C encerra o monitor com saida diferente de zero; nao deve interromper o registro no csv.
pio device monitor | tee "$MONITOR_LOG" || true

MAC_ADDRESS="$(grep -o 'MAC da placa: [0-9A-Fa-f:]\+' "$MONITOR_LOG" | tail -1 | awk '{print $NF}')"
if [[ -n "$MAC_ADDRESS" ]]; then
  if [[ ! -f "$CSV_FILE" ]]; then
    echo "timestamp,mac_address" > "$CSV_FILE"
  fi
  echo "$(date -Iseconds),${MAC_ADDRESS}" >> "$CSV_FILE"
  echo "MAC ${MAC_ADDRESS} registrado em ${CSV_FILE}"
fi
