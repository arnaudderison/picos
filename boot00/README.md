# 🧠 PicOS — Comprendre le Bootloader (de zéro)

Un os ?

---

## 🚀 C’est quoi un bootloader ?

Un **bootloader** (ou **chargeur d’amorçage**) est le **tout premier programme** qui s'exécute **quand un ordinateur démarre**.

Il est **chargé en mémoire par le BIOS**, directement depuis un **disque dur**, une **clé USB**, un **CD**, etc.

> 🌟 Son but : préparer le terrain pour charger et démarrer un vrai système d’exploitation (comme Linux, Windows, ou ton propre OS).

---

## 📁 Étapes au démarrage d’un PC :

1. ⚙️ **Le BIOS** (firmware de la carte mère) s’allume.
2. 🔍 Il cherche un périphérique de démarrage (disque, USB…).
3. 📆 Il lit **les 512 premiers octets** du disque (le **boot sector**).
4. 📀 Il copie ce code à l’adresse **0x7C00** en mémoire.
5. 🚀 Il **saute à cette adresse** et commence à **exécuter ton bootloader**.

---

## 🧬 Pourquoi seulement **512 octets** ?

🔊 Parce que **le secteur de boot** est une **zone standard de 512 octets**.
C’est une **limite matérielle** vieille, mais toujours en usage.

### 🧪 Structure d’un secteur de boot :

* `510 premiers octets` : ton code assembleur
* `2 derniers octets` : la signature magique `0x55AA`
  (⚠️ sans elle, le BIOS ignore ton code)

---

## 🔹 Pourquoi du **code 16 bits** (et pas 32 ou 64 bits) ?

Quand un PC démarre, il est en **mode réel** (**real mode**), un **mode de compatibilité hérité des années 80**, où :

* Le CPU exécute **du code 16 bits**
* Il n’a accès qu’à **1 Mo de mémoire**
* Les interruptions BIOS fonctionnent

> 👳 Ce mode existe pour être compatible avec les tout premiers PC (comme le IBM PC de 1981).
> C’est pourquoi **on démarre comme en 1980**, même sur un PC moderne.

---

## 🖥️ Que peut faire un bootloader simple ?

Avec seulement 512 octets, on peut :

* Afficher un texte à l'écran (`Hello`)
* Lire un secteur depuis le disque
* Passer le contrôle à un **noyau plus complexe** (kernel en C par exemple)

---

## 🛠️ Outils nécessaires (Ubuntu)

```bash
sudo apt install nasm qemu-system-x86
```

* `nasm` : assembleur pour créer du code binaire
* `qemu` : pour tester ton OS sans redémarrer ton vrai PC

---

## 💠 Exemple de bootloader ultra simple

```nasm
[BITS 16]          ; Code 16 bits (mode réel)
[ORG 0x7C00]       ; BIOS charge ici

mov ah, 0x0E       ; Mode "teletype"
mov al, 'H'        ; Caractère à afficher
int 0x10           ; Appel BIOS → affiche le caractère

jmp $              ; Boucle infinie

times 510 - ($ - $$) db 0 ; Remplissage jusqu'à 510 octets
dw 0xAA55                 ; Signature obligatoire
```

---

## ⚙️ Compilation

```bash
nasm -f bin boot.asm -o os.img
```

## 🚀 Lancement avec QEMU

```bash
qemu-system-i386 -fda os.img
```

Une fenêtre s’ouvre, et tu vois `H` en haut à gauche :
🎉 **Ton propre système d’exploitation vient de booter !**

---

## 🔎 À retenir

| Élément    | Rôle                                                   |
| ---------- | ------------------------------------------------------ |
| `BIOS`     | Démarre le système et charge le bootloader             |
| `0x7C00`   | Adresse mémoire où le BIOS place le bootloader         |
| `16 bits`  | Mode de compatibilité du CPU au démarrage              |
| `int 0x10` | Interruption BIOS pour afficher un caractère           |
| `0xAA55`   | Signature obligatoire à la fin du bootloader           |
| `jmp $`    | Boucle infinie (évite d’exécuter n’importe quoi après) |

---

## 📚 Pour aller plus loin

* [https://wiki.osdev.org/Bootloader](https://wiki.osdev.org/Bootloader)
* [https://github.com/cfenollosa/os-tutorial](https://github.com/cfenollosa/os-tutorial)
* [https://www.youtube.com/watch?v=Fbzl1cQ5z\_o](https://www.youtube.com/watch?v=Fbzl1cQ5z_o) (vidéo claire en anglais)

---

## 🧑‍💻 Auteur

Projet initié par **Arnaud Derison** – pour comprendre les entrailles d’un vrai OS 🧠
