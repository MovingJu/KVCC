#!/usr/bin/env bash
# One-time setup after "Use this template": GitHub does not copy rulesets or merge
# settings from a template, so apply them with the GitHub CLI (needs admin rights).
# Usage: .github/bootstrap.sh [OWNER/NAME]   (default: the repo of the current directory)
set -euo pipefail
cd "$(git rev-parse --show-toplevel)"

REPO="${1:-$(gh repo view --json nameWithOwner --jq .nameWithOwner)}"
RULESET=".github/rulesets/main.json"
NAME="$(sed -n 's/^  "name": "\(.*\)",$/\1/p' "$RULESET")"

echo "Squash-only merges, PR title as commit message ($REPO)"
gh api -X PATCH "repos/$REPO" --input - >/dev/null <<'EOF'
{
  "allow_squash_merge": true,
  "allow_merge_commit": false,
  "allow_rebase_merge": false,
  "squash_merge_commit_title": "PR_TITLE",
  "squash_merge_commit_message": "BLANK",
  "delete_branch_on_merge": true
}
EOF

echo "Ruleset: $NAME"
ID="$(gh api "repos/$REPO/rulesets" --jq ".[] | select(.name == \"$NAME\") | .id")"
if [ -n "$ID" ]; then
  gh api -X PUT "repos/$REPO/rulesets/$ID" --input "$RULESET" >/dev/null
else
  gh api -X POST "repos/$REPO/rulesets" --input "$RULESET" >/dev/null
fi
echo "Done."
