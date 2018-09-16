/*-
 * Copyright (c) 2018 Florian Limberger <flo@snakeoilproductions.net>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modification.
 * 2. Redistributions in binary form must reproduce at minimum a disclaimer
 *    substantially similar to the "NO WARRANTY" disclaimer below
 *    ("Disclaimer") and any redistribution must be conditioned upon
 *    including a substantially similar Disclaimer requirement for further
 *    binary redistribution.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 */

#include <err.h>
#include <signal.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
	struct sigaction	sigact;

	if (argc < 2) {
		fprintf(stderr, "usage: %s CMD [ARGS...]\n", argv[0]);

		return 2;
	}

	bzero(&sigact, sizeof(sigact));

	/* unblock signals */
	if (sigemptyset(&sigact.sa_mask) < 0)
		err(1, "sigemptyset");
	if (sigaddset(&sigact.sa_mask, SIGINT) < 0)
		err(1, "sigaddset(SIGINT)");
	if (sigaddset(&sigact.sa_mask, SIGTERM) < 0)
		err(1, "sigaddset(SIGTERM)");
	if (sigprocmask(SIG_UNBLOCK, &sigact.sa_mask, NULL) < 0)
		err(1, "sigprocmask");

	/* set default handler for signals */
	if (sigemptyset(&sigact.sa_mask) < 0)
		err(1, "sigemptyset");
	sigact.sa_handler = SIG_DFL;
	if (sigaction(SIGINT, &sigact, NULL) < 0)
		err(1, "sigaction(SIGINT)");
	if (sigaction(SIGTERM, &sigact, NULL) < 0)
		err(1, "sigaction(SIGTERM)");

	execvp(argv[1], &argv[1]);
	err(1, "execvp");
}
