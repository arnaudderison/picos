[bits 32]
extern irq_handler
; Fonction ASM qui gère l'interruption 0x21 (IRQ1 = clavier)
[global isr33]
isr33:
    pusha                   ; sauvegarde tous les registres généraux
    push 0x21            ; push du numéro d'interruption (utilisé dans irq_handler)
    call irq_handler 
    add esp, 4              ; nettoyage de la pile après l'appel (remove le 33)
    popa                    ; restauration des registres
    iretd                   ; retour de l'interruption


; Handler par défaut pour les interruptions non gérées (fait juste un retour)
[global default_handler]
default_handler:
    iretd