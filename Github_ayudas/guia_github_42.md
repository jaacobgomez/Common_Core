# Guía — mañana en 42

## Antes de salir de casa (esta noche o antes de irte)

- [ ] Pon `Common_Core` en **público** temporalmente:
  GitHub → `Common_Core` → Settings → General → Danger Zone → Change visibility → Public
- [ ] Consulta en la intranet la URL de vogsphere asignada a **Libft** (la de C_Piscine_Reloaded ya la tienes).

## En el ordenador de 42

### 1) Clona tu mono-repo

```bash
git clone https://github.com/jaacobgomez/Common_Core.git
cd Common_Core
```

### 2) Conecta los remotos de 42 (uno por proyecto)

```bash
git remote add fortytwo-piscine git@vogsphere-v2.42madrid.com:vogsphere/intra-uuid-bb77b08c-6c53-4dee-b58a-a14a4712cd2d-jacgomez
git remote add fortytwo-libft git@vogsphere-v2.42madrid.com:vogsphere/<ruta-libft>
```

### 3) Sube cada proyecto a su repo de 42

```bash
git subtree push --prefix=C_Piscine_Reloaded fortytwo-piscine master
git subtree push --prefix=Libft fortytwo-libft master
```

> ⚠️ Si alguno de los dos da `rejected` o `unrelated histories` (porque vogsphere ya tenía un commit inicial propio), NO fuerces. En su lugar:
> ```bash
> git subtree pull --prefix=<carpeta> fortytwo-<proyecto> master --allow-unrelated-histories
> git subtree push --prefix=<carpeta> fortytwo-<proyecto> master
> ```

### 4) Verifica

```bash
git remote -v
git log --oneline -5
```
Y opcionalmente abre la URL del repo de 42 en el navegador para confirmar que aparecen los archivos.

## Antes de irte de 42

- [ ] Si has avanzado código en 42, súbelo también a tu mono-repo:
  ```bash
  git add -A
  git commit -m "..."
  git push origin master
  ```
- [ ] Vuelve a poner `Common_Core` en **privado** en GitHub (Settings → Danger Zone → Change visibility → Private).

## Rutina para el resto de proyectos que vayan saliendo

1. Trabajas el proyecto donde sea (casa o 42), dentro de `Common_Core/<proyecto>/`.
2. `git add -A && git commit -m "..." && git push origin master`.
3. Cuando quieras que 42 lo corrija:
   ```bash
   git remote add fortytwo-<proyecto> <url-vogsphere-del-proyecto>   # solo la primera vez
   git subtree push --prefix=<proyecto> fortytwo-<proyecto> master
   ```
   (el `push fortytwo-*` solo funciona desde la red de 42, por el bloqueo del puerto 22 desde casa)
