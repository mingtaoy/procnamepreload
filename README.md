# procnamepreload

A trivial DSO to LD_PRELOAD into processes which will invoke `prctl(PR_SET_NAME, ...)` as a static initializer.

This can be used to set distinguishable `comm` values for workloads that are typically invoked with another launcher: (e.g. `java -jar` or `python3`).

This can be helpful in conjunction with `bpf_get_current_comm` when running a BPF program under process context.
