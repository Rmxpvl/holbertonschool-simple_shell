```mermaid
---
config:
  layout: dagre
---
flowchart TB
    A(["main"]) --> B["run_shell"]
    B --> C{"isatty STDIN?"}
    C -- oui --> D["write $"]
    C -- non --> E["getline"]
    D --> E
    E --> F{"nread == -1?"}
    F -- oui --> G{"isatty?"}
    G -- oui --> H["write newline"]
    G -- non --> I(["free line · return last_status"])
    H --> I
    F -- non --> J["strip newline\nparse_line · strtok"]
    J --> K{"argc == 0?"}
    K -- oui --> C
    K -- non --> L{"handle_builtins\ncmd == ?"}
    L -- exit --> M(["free line · exit last_status"])
    L -- env --> N["print environ\nline_num++"]
    N --> C
    L -- aucun --> O["execute"]
    O --> P{"slash dans cmd?"}
    P -- oui --> Q{"access F_OK?"}
    Q -- non --> R["stderr not found\nreturn 127"]
    R --> C
    Q -- oui --> S{"S_ISDIR?"}
    S -- oui --> T["stderr perm denied\nreturn 126"]
    T --> C
    S -- non --> U{"access X_OK?"}
    U -- non --> T
    U -- oui --> V["path = args0"]
    P -- non --> W["find_in_path"]
    W --> W1["_getenv PATH"]
    W1 --> W2{"PATH vide?"}
    W2 -- oui --> X["stderr not found\nreturn 127"]
    X --> C
    W2 -- non --> W3@{ label: "strdup · strtok ':'" }
    W3 --> W4{"dir suivant?"}
    W4 -- non --> X
    W4 -- oui --> W5["build_path dir/cmd"]
    W5 --> W6{"access X_OK?"}
    W6 -- non --> W4
    W6 -- oui --> V
    V --> Y["fork_execute"]
    Y --> Z["fork"]
    Z --> Z1{"pid == -1?"}
    Z1 -- oui --> Z2["perror fork\nreturn 1"]
    Z2 --> C
    Z1 -- non --> Z3{"pid == 0?\nenfant"}
    Z3 -- oui --> Z4["execve path args environ"]
    Z4 -- succes --> Z5(["process remplacé"])
    Z4 -- echec --> Z6(["stderr not found · exit 127"])
    Z3 -- non parent --> Z7["waitpid"]
    Z7 --> Z8{"WIFEXITED?"}
    Z8 -- oui --> Z9["return WEXITSTATUS"]
    Z8 -- non --> Z10["return 1"]
    Z9 --> Z11["last_status = res\nline_num++"]
    Z10 --> Z11
    Z11 --> C

    W3@{ shape: rect}
    style A fill:#7aa2f7,color:#1a1b26,stroke:none
    style I fill:#f7768e,color:#1a1b26,stroke:none
    style M fill:#f7768e,color:#1a1b26,stroke:none
    style Z5 fill:#9ece6a,color:#1a1b26,stroke:none
    style Z6 fill:#f7768e,color:#1a1b26,stroke:none
    ```